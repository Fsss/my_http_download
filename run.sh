#!/bin/bash

#定义环境变量ROOT为当前路径
export ROOT=`pwd`
if [ $# == 0 ]; then
	mkdir bin;
	cd src/;
	make;
elif [ $# == 1 ]; then
	if [ $1 == 'clean' ]; then
		rm -rf bin/*.o bin/main;
	fi
fi
