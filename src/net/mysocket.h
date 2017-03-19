#ifndef __MYSOCKET_H__
#define __MYSOCKET_H__

#include"../init/mydefine.h"
#include"../init/mylog.h"
#include"../init/myconfig.h"
#include"../work/mywork.h"
#define SOCKET int

#include<unistd.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<sys/socket.h>

int _monitor_port;
char _monitor_ip[50];
SOCKET _server_socket;
struct sockaddr_in _addr_in;

int init_socket(const char * ip_, const char * port_);
int get_socket();
int socket_listen();
void server_work();

#endif
