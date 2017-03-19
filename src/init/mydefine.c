#include"mydefine.h"
#include<string.h>
#include<stdlib.h>

//查找字串位置
int find_pos_str(const char * str_, const char * substr_)
{
	return strstr(str_, substr_) - str_;
}
//截取字符串str的[begin, end)
char * get_substr(const char * str_, int begin_, int end_)
{
	int len = end_ - begin_;
	char * ret_str = (char *)calloc(len + 1, sizeof(char));
	strncpy(ret_str, str_ + begin_, len);
	ret_str[len] = '\0';
	return ret_str;
}
