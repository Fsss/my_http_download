#ifndef __MYWORK_H__
#define __MYWORK_H__

#include"../init/mydefine.h"
#include"../init/mylog.h"
#include"../http/myrequest.h"
#include"../http/myresponse.h"
#include<dirent.h>

void deal_request(const char * receive_buffer_, char * send_message_);
void set_file_name();
void get_file_name();
void set_response_static_page();
void add_msg_body(const char * file_name_);

#endif
