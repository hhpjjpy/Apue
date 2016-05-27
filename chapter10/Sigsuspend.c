/*
 * Sigsuspend.c
 * 保护代码临界区，使其不被特定信号中断的正确方法。
 *  Created on: 2016年3月12日
 *      Author: haipinghu
 */
#include "apue.h"

static void sig_int(int);

int main(void){
	sigset_t newmask,oldmask,waitmask;

	pr_mask("program start : ");

	if(signal(SIGINT,sig_int) == SIG_ERR)
		err_sys("signal(SIGINT,sigint) is error ");
	sigemptyset(&waitmask);
	sigaddset(&waitmask,SIGUSR1);

	sigemptyset(&newmask);
	sigaddset(&newmask,SIGINT);

	if(sigprocmask(SIG_BLOCK,&newmask,&oldmask) < 0 )
		err_sys("SIG_BLOCK error ");
	/*
	 *阻塞信号后，可以在此编写临界区代码。
	 */
	pr_mask("in critical regin 1\n");
	int i = 100000;
	while(i--);
	sleep(10);
	pr_mask("in critical regin 2\n");

	if(sigsuspend(&waitmask) != -1)
		err_sys("sigsuspend error ");
	pr_mask("after return from sigsuspend ");

	if(sigprocmask(SIG_SETMASK,&oldmask,NULL) < 0 )
		err_sys(" SIG_SETMASK is error ");
	sleep(10);
	pr_mask(" program exit : ");
	exit(0);
}

static void sig_int(int signo){
	pr_mask("\n in sig_int : ");
}



