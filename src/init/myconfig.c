#include"myconfig.h"
#include"mydefine.h"
#include<stdio.h>
#include<string.h>

//初始化配置文件名以及配置参数个数及解析
void config_init(char * file_name_)
{
	file_name = file_name_;
	_key_num = 0;parse_file();
}

//查看解析了的配置文件
void print_key_value()
{
	for (int i = 1; i <= _key_num; i++) {
		printf("[%s]-->[%s]\n", _key[i], _value[i]);
	}
}

//用配置名匹配值
int get_value(char * key_)
{
	int i, j, len, key_len=strlen(key_);
	for (i = 1; i <= _key_num; i++) {
		len = strlen(_key[i]);
		if (len != key_len) continue ;
		for (j = 0; j < len; j++)
		if (key_[j] != _key[i][j]) break ;
		if (j == len) return i;
	}
	return 0;
}

//解析配置文件
void parse_file()
{
	FILE * file = NULL;
	file = fopen(file_name, "r");
	if (file == NULL) {
		printf("The file is not found!\n");
		return ;
	}

	char s[N], s1[N], s2[N];
	int i, j, len, len1, len2;
	while (fgets(s,N,file) != NULL) {
		len = strlen(s);
		if (len <= 1) continue ;
		
		_key_num++;
		len1 = len2 = 0;

		for (i= 0; i < len; i++)
		if (s[i] == '=') break ;
		else s1[len1++] = s[i];
		for (i++; i < len; i++) s2[len2++]=s[i];
		
		_key[_key_num][len1] = '\0';
		_value[_key_num][len2] = '\0';

		for (j = 0, i = 0; i < len1; i++) {
			if (s1[i] == '\n') { _key[_key_num][i]='\0'; break ; }
			if (s1[i] != ' ') _key[_key_num][j++] = s1[i];
		}
		
		for (j = 0, i = 0;i < len2; i++) {
			if (s2[i] == '\n') { _value[_key_num][i]='\0'; break ; }
			if (s2[i] != ' ') _value[_key_num][j++] = s2[i];
		}
	}
	fclose(file);
}
