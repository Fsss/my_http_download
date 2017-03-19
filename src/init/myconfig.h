#ifndef __MYCONFIG_H__
#define __MYCONFIG_H__

#include"mydefine.h"

int _key_num;
char _key[N][N];
char * file_name;
char _value[N][N];

void parse_file();
void print_key_value();
int get_value(char * key_);
void config_init(char * file_name_);

#endif
