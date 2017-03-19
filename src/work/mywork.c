#include"mywork.h"
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
int _flag = 0;
char _dir[1024];

void deal_request(const char * receive_buffer_, char * send_message_)
{
	init_response();
	parse_request(receive_buffer_);
	
	//printf("TEST!!!request\n");   //test
	//printf("%s\n", receive_buffer_);

	if (!strcmp(_method, "GET")) {
		_flag = 0;
		if (!strlen(_path) || !strcmp(_path, "/")) {
			_flag = 1;
			strcpy(_path, "/src/html/index.html");
		}
		int dot_pos = strrchr(_path, '.') - _path;
		if (dot_pos < strlen(_path)) {
			char * suffix = get_substr(_path, dot_pos + 1, strlen(_path));
			
			if (!strcmp(suffix, "html")) {
				set_msg_head("Content-Type: text/html; charset=utf-8\r\n");
			} else if (!strcmp(suffix, "css")) {
				set_msg_head("Content-Type: text/css\r\n");
			} else if (!strcmp(suffix, "js")) {
				set_msg_head("Content-Type:	application/x-javascript; charset=utf-8\r\n");
			} else set_file_name();
		} else set_file_name();
		
		set_response_static_page();
		set_msg_body_len();

		content_response(send_message_);
	} else {
		strcpy(_status, "405\r\n");
	}
}
void set_file_name()
{
	int file_begin = strrchr(_path, '/') - _path;
	char * file_name = get_substr(_path, file_begin + 1, strlen(_path));
	strcat(file_name, "\r\n");
	char tmp[1024]={0};
	strcpy(tmp, "Content-Type: application/octet-stream\r\n");
	strcat(tmp, "Content-Disposition: attachment;fileName=");
	set_msg_head(strcat(tmp, file_name));
}
//读取下载目录下的文件
void get_file_name()
{
	DIR * directory_pointer;
	struct dirent * entry;
	add_msg_body("<body>\n<h1>下载列表</h1>\n");
	
	if ((directory_pointer = opendir("../docroot/")) == NULL) 
		printf("Error opening!\n");
	else {
		while ((entry = readdir(directory_pointer)) != NULL) {
			if (entry->d_name[0] == '.') continue ;
			char tmp[1024]={0};
			sprintf(tmp, "%s%s%s%s%s\n", "<a href=\"../docroot/", 
					entry->d_name, "\">", entry->d_name, "</a>");
			add_msg_body(tmp);
		}
		closedir(directory_pointer);
	}
	
	add_msg_body("</body>\n</html>\n");
}
void add_msg_body(const char * file_name_)
{
	strcat(_msg_body, file_name_);
}
//构建返回页面的报文
void set_response_static_page()
{
	strcpy(_dir, "..");
	strcat(_dir, _path);
	FILE * file = NULL;
	file = fopen(_dir, "rb");
	if (file == NULL) {//下载页面未找到，跳转404
		printf("404 NOT FOUND!\n");
		set_msg_head("Content-Type: text/html; charset=utf-8\r\n");
		strcpy(_status, "404 NOT FOUND\r\n");
		strcpy(_dir, "../src/html/404.html");
		file = fopen(_dir, "rb");
	}
	if (file == NULL) return ;//两个页面都打开失败

	fseek(file, 0, SEEK_END);
	_body_len = ftell(file);
	rewind(file);
	_msg_body = (char *)malloc(sizeof(char) * _body_len * 10 + 1);
	//读出页面内容
	_body_len = fread(_msg_body, sizeof(char), _body_len, file);
	//test
	//printf("TEST!!!web");
	//printf("%s\n", _msg_body);

	if (_flag) {
		get_file_name();
		_body_len = strlen(_msg_body);
	}
	fclose(file);
}
