/*
 * IdTest.c
 *
 *  Created on: 2016年2月23日
 *      Author: haipinghu
 */
#include "apue.h"
#include <unistd.h>

int
main(void){
	printf("all id of process \n");

	printf("pid:%d,ppid:%d,uid:%d,euid:%d,gid:%d,egid:%d \n",(long)getpid(),
			(long)getppid(),(long)getuid(),(long)geteuid(),(long)getgid(),getegid());
}


