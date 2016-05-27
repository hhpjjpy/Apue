/*
 * ForkTest.c
 *
 *  Created on: 2016年2月23日
 *      Author: haipinghu
 */
#include "apue.h"
#include <unistd.h>

int
main(void){
	int val = 100;
	pid_t  pid;

	if( (pid=fork())<0)
		err_sys("fork error \n");
	else if(pid == 0){ //子进程
		val+=100;
	}else{
		val -= 50;
	}

	printf("pid:%d,ppid:%d,val:%d \n",(long)getpid(),(long)getppid(),val);
}



