#include"myresponse.h"
#include<stdio.h>
#include<string.h>

void set_msg_body_len()
{
	char clen[20];
	sprintf(clen, "%lld", _body_len);
	strcpy(_cont_len, "Content-Length:");
	strcat(_cont_len, clen);
	strcat(_cont_len, "\r\n");
}
void set_msg_head(const char * value_)
{
	strcpy(_response.msg_head, value_);
}
void init_response()
{
	strcpy(_response.version, "HTTP/1.1 ");
	strcpy(_status, "200 OK\r\n");
}
//将响应的各部分组合在一起
void content_response(char * send_message_)
{
	strcat(send_message_, _response.version);
	strcat(send_message_, _status);
	strcat(send_message_, _response.msg_head);
	strcat(send_message_, _cont_len);
	strcat(send_message_, "\r\n");

	strcat(send_message_, _msg_body);
	//printf("TEST!TEST!TEST!\n");
	//printf("%s\n", _msg_body);
}
