#include"../init/mydefine.h"
#include"../init/mylog.h"
#include"../init/myconfig.h"
#include"../net/mysocket.h"

int main()
{
	config_init("../etc/myconfig.con");
	print_key_value();
	log_init(_value[get_value("logfile")]);
	int ret = init_socket(_value[get_value("listenip")], 
						_value[get_value("listenport")]);
	// printf("TEST  init_socket=%d\n", ret);
	if (ret == 1) server_work();
	return 0;
}
