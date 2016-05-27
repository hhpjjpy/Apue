/*
 * LongjmpSignal.c
 *
 *  Created on: 2016年3月2日
 *      Author: haipinghu
 */
#include "apue.h"
#include <setjmp.h>

static void sig_alrm(int);
static jmp_buf env_alrm;

int
main(void){
	int n;
	char line[MAXLINE];

	if(signal(SIGALRM,sig_alrm) == SIG_ERR)
		err_sys(" signal(SIGALRM) error \n");
	setjmp(env_alrm);
	alarm(10);

	if( (n= read(STDIN_FILENO,line,MAXLINE)) <0 )
		err_sys(" read error \n");
	alarm(0);

	write(STDOUT_FILENO,line,n);
	exit(0);
}

static void
sig_alrm(int signo){
	printf(" sig_alrm is run \n");
	longjmp(env_alrm,1);
}



