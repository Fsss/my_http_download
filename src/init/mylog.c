#include"mylog.h"
#include<time.h>
#include<stdio.h>
#include<stdarg.h>
#include<string.h>

int _cnt=0;

//初始化日志文件路径
void log_init(char * logfile_)
{
	_log_file = logfile_;
}
//写入日志文件
void write_log(char * fmt_, ...)
{
	memset(_log_buf, 0, LOG_SIZE);
	FILE * file = NULL;
	file = fopen(_log_file, "a");

	//获得系统当前的时间，然后写入日志文件
	time_t t = time(NULL);
	struct tm * cur_time = localtime(&t);
	char fmt_buff[255] = {0};
	sprintf(fmt_buff, "[%4d-%02d-%02d %02d:%02d:%02d]\n",
			cur_time->tm_year + 1900, cur_time->tm_mon + 1,
			cur_time->tm_mday, cur_time->tm_hour,
			cur_time->tm_min, cur_time->tm_sec);
	fputs(fmt_buff, file);
	
	//读取fmt后面的参数
	va_list arg;
	va_start(arg, fmt_);
	_cnt = vsprintf(_log_buf, fmt_, arg);
	va_end(arg);
	fputs(_log_buf, file);
	fputs("\n", file);
 	fclose(file);
}
