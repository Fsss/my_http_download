#ifndef __MYRESPONSE_H__
#define __MYRESPONSE_H__

#include"myhttp.h"
#include"../init/mydefine.h"

char _status[50];
char * _msg_body;
char _cont_len[300];
long long _body_len;
struct my_http _response;

void set_msg_body_len();
void set_msg_head(const char * value_);
void init_response();
void content_response(char * send_message_);

#endif
