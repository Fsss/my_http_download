#include"mysocket.h"
#include<time.h>
#include<string.h>
#include<pthread.h>

//服务器端获取socket描述符，并赋值ip+端口，然后开始监听这个socket
int init_socket(const char * ip_, const char * port_)
{
	strcpy(_monitor_ip, ip_);
	_monitor_port = 0;
	for (const char *ch = port_; *ch; ch++) 
		_monitor_port = _monitor_port * 10 + (*ch - '0');

	int ret = get_socket();
	if (ret != RT_OK) {
		printf("GET SOCKET ERROR!\n");
		return ret;
	}

	ret = socket_listen();
	if (ret != RT_OK) {
		if (ret == 3) printf("BIND ERROR!\n");
		else if (ret == 4) printf("LISTEN ERROR!\n");
		return ret;
	}

	//printf("TEST  socket init success ip=%s   port=%d\n", 
	//	_monitor_ip, _monitor_port);
	
	return RT_OK;
}
//获取socket描述符，AF_INET为ipv4地址类型，SOCK_STREAM为TCP协议类型
int get_socket()
{
	_server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (_server_socket < 0) return RT_ERR_SOCKET;
	return RT_OK;
}
//给socket赋值ip+端口，然后开始监听
int socket_listen()
{
	//将主机字节序转换成网络字节序
	_addr_in.sin_addr.s_addr = inet_addr(_monitor_ip);
	_addr_in.sin_family = AF_INET;
	_addr_in.sin_port = htons(_monitor_port);
	
	int ret = bind(_server_socket, (struct sockaddr*)&_addr_in,
					sizeof(struct sockaddr));
	if (ret < 0) {
		close(_server_socket);
		return RT_ERR_BIND;
	}
	
	ret = listen(_server_socket, 512);//最多的请求响应的个数
	if (ret < 0) {
		close(_server_socket);
		return RT_ERR_LISTEN;
	}
	printf("LISTENNING!\n");
	return RT_OK;
}



pthread_mutex_t _mutex;
//执行线程
void connect_thread_entrance(SOCKET *connect_socket_)
{
	char receive_buffer[BUFMAX];
	char send_message[BUFMAX];
	memset(receive_buffer, 0, BUFMAX);
	//读取请求内容
	int ret = recv(*connect_socket_, receive_buffer, BUFMAX, 0);
	
	if (ret < 0) {//读取出错
		close(*connect_socket_);
		pthread_exit(NULL);
		return ;
	} else if (!ret) {//文件结束
		close(*connect_socket_);
		pthread_exit(NULL);
		return ;
	}
	//构建响应信息
	memset(send_message, 0, BUFMAX);
	deal_request(receive_buffer, send_message);
	printf("NOW IN THREAD!\n");
	ret=send(*connect_socket_, send_message, strlen(send_message), 0);
	
	//写入日志文件
	pthread_mutex_lock(&_mutex);
	write_log(receive_buffer);
	write_log(send_message);
	pthread_mutex_unlock(&_mutex);
	
	close(*connect_socket_);
	pthread_exit(NULL);//等待结束线程
	return ;
}
//初始化互斥锁，接受请求然后创建新线程
void server_work()
{
	socklen_t size;
	pthread_mutex_init(&_mutex, NULL);//初始化锁
	while (1) {
		//客户的socket描述符
		struct sockaddr_in client_socket;
		SOCKET connect_socket;
		connect_socket = accept(_server_socket,
					(struct sockaddr * ) &client_socket, &size);
		//创建线程
		pthread_t thread_id;
		int ret = pthread_create(&thread_id, NULL, 
					(void *)connect_thread_entrance, 
					(void *)&connect_socket);

		if (ret == -1) {
			printf("Pthread create fail!\n");
			continue ;
		}
		pthread_join(thread_id, NULL);//等待一个线程的结束
	}
}


