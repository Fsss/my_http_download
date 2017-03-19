#include"myrequest.h"
#include<string.h>
char _str[BUFMAX];

int parse_request(const char * receive_buffer_)
{
	strcpy(_str, receive_buffer_);
	int ret = parse_request_head();
	ret = parse_request_msg_head();
	return ret;
}
//解析请求的第一行
int parse_request_head()
{
	char first_line[100];
	int end = find_pos_str(_str, "\r\n");
	strcpy(first_line, get_substr(_str, 0, end));
	strcpy(_method, strtok(first_line, " "));
	strcpy(_uri, strtok(NULL, " "));
	strcpy(_path, _uri);
	strcpy(_request.version, strtok(NULL, " "));
	//printf("method=%s  uri=%s  version=%s\n", _method, _uri, _request.version);
	return RT_OK;
}
//解析请求头
int parse_request_msg_head()
{
	int begin = find_pos_str(_str, "\r\n");
	int end = find_pos_str(_str, "\r\n\r\n");
	strcpy(_request.msg_head, get_substr(_str, begin+2, end));
	//printf("requset_msg_head=%s\n", _request.msg_head);
	return RT_OK;
}
