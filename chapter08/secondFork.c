/*
 * secondFork.c
 *
 *  Created on: 2016年2月23日
 *      Author: haipinghu
 */
//如果一个进程fork()一个子进程，但不要它等待子进程终止，也不希望子进程处于僵尸状态直到
//父进程终止，实现这一要求的诀窍是调用fork两次。终止第一个子进程，让第二个子进程的父进程变为init。

#include "apue.h"
#include <sys/wait.h>

int
main(void){
	pid_t pid;
	if( (pid = fork()) < 0 )
		err_sys(" fork is error ");
	if(pid==0){//第一个子进程
		if( (pid=fork())<0)
			err_sys(" fork is error ");
		else if(pid > 0){
			exit(0);//第一个进程马上退出
		}else{ //第二个进程，在第一个进程退出后，第二个进程的父进程将会变为init，即将其退出处理交由系统。
			sleep(2);
			printf("pid:%d,ppid:%d \n",(long)getpid(),(long)getppid());
			exit(0);
		}
	}
	printf(" the child pid:%d \n",pid);
	//父进程，等待第一个进程
	if(waitpid(pid,NULL,0) != pid)
		err_sys(" waitpid is error ");
	exit(0);
}



