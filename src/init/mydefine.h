#ifndef __MY_DEFINE_H__
#define __MY_DEFINE_H__

#include<stdio.h>
#define N 100
#define BUFMAX 40960
#define LOG_SIZE 10240
#define LOG(a) printf("%s\n", a);

enum {
	RT_ERR,
	RT_OK,
	RT_ERR_SOCKET,
	RT_ERR_BIND,
	RT_ERR_LISTEN
};

char * get_substr(const char * str_, int begin_, int end_);
int find_pos_str(const char * str_, const char * substr_);

#endif
