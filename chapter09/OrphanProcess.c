/*
 * OrphanProcess.c
 *
 *  Created on: 2016年2月25日
 *      Author: haipinghu
 */
#include "apue.h"
#include <errno.h>

static void sig_hup(int signo){
	printf(" SIGHUP received ,pid = %ld \n",(long)getpid());
}
static void pr_ids(char *name){
	printf(" %s : pid = %ld, ppid = %ld ,pgrp = %ld,tpgrp = %ld \n",
			name,(long)getpid(),(long)getppid(),(long)getpgrp(),(long)tcgetpgrp(STDIN_FILENO));

	fflush(stdout);
}

int
main(void){
	pid_t pid;
    char c;
    pr_ids("parent");
    if( (pid = fork())<0)
    	err_sys(" fork is error ");
    if(pid>0){
    	sleep(15);//父进程休眠5秒，保证子进程，有充分的时间，挂起自己。
    }else{
    	pr_ids(" child_frist ");
    	if(read(STDIN_FILENO,&c,1)!=1)
    	    	printf(" read is error \n");
    	else
    		write(STDOUT_FILENO,&c,1);

    	signal(SIGHUP,sig_hup);//当父进程终止后，进程组包含一个停止的子进程。进程组成为孤儿进程组。posix.1要求向
    	//向新孤儿进程中处于停止状态的每一个进程发送挂断信号（SIGHUP,对于挂断信号系统默认是终止该进程，此处自己做了处理），
    	//接着又发送继续信号(SIGCONT)
    	kill(getpid(),SIGTSTP);
    	pr_ids(" child_second ");//此时父进程已终止，子进程的父进程变为init。变为后台进程组，不能在读取终端的内容。
    	//此时read将定位在NULL文件上，故读取失败。

    	if(read(STDIN_FILENO,&c,1)!=1){
    		printf(" read is error \n");
    	}
    }

    exit(0);

}



