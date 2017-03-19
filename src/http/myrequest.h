#ifndef __MYREQUEST_H__
#define __MYREQUEST_H__

#include"myhttp.h"
#include"../init/mydefine.h"

char _method[20];
char _uri[1024];
char _path[1024];
struct my_http _request;

int parse_request(const char * _receive_buffer);
int parse_request_head();
int parse_request_msg_head();

#endif
