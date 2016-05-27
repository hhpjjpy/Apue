/*
 * Sigsuspend2.c
 * 使用sigsuspend()函数，等待一个信号处理程序设置一个全局变量。
 *  Created on: 2016年3月12日
 *      Author: haipinghu
 */
#include "apue.h"

volatile sig_atomic_t quitflag;

static void sig_int(int signo){
	if(signo == SIGINT){
		printf("interrupt \n");
	}else if(signo == SIGQUIT){
		quitflag = 1;
	}
}

int main(void){
	sigset_t newmask,oldmask,zeromask;

	if(signal(SIGINT,sig_int) == SIG_ERR)
		err_sys("signal(SIGINT,sig_int) error");
	if(signal(SIGQUIT,sig_int) == SIG_ERR)
		err_sys("signal(SIGOUIT,sig_int) error");

	sigemptyset(&zeromask);
	sigemptyset(&newmask);
	sigemptyset(&oldmask);

	if(sigprocmask(SIG_BLOCK,&newmask,&oldmask) < 0 )
		err_sys("SIG_BLOCK error ");


	while(quitflag == 0)
		sigsuspend(&zeromask);
	quitflag = 0;

	if(sigprocmask(SIG_SETMASK,&oldmask,NULL) < 0 )
		err_sys(" SIG_SETMASK is error ");

	exit(0);
}


