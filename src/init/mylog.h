#ifndef __MYLOG_H__
#define __MYLOG_H__

#include"mydefine.h"

char * _log_file;
char _log_buf[LOG_SIZE];

void log_init(char * logfile_);
void write_log(char * fmt_,...);

#endif
