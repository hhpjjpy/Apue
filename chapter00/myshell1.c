/*
 * myshell1.c
 *
 *  Created on: 2016年2月18日
 *      Author: haipinghu
 */

#include "apue.h"

void signal_deal(){
	printf(" hava a signal  interrupt \n");
}

int
main(void){
	char buf[MAXLINE];
	pid_t pid;
	int status;
	printf("&");
	while(fgets(buf,MAXLINE,stdin)!= NULL){
		if(buf[strlen(buf)-1]=='\n')
			buf[strlen(buf)-1]=0;
		if((pid=fork())<0){
			err_sys("fork error");
		}
		if(pid== 0){
			execlp(buf,buf,(char*)0);
			err_ret("couldn't execute : %s ",buf);
			exit(127);
		}
		if((pid==waitpid(pid,&status,0))<0)
			err_sys("waitpid error");
		printf("&");
	}

	if(signal(SIGINT,signal_deal)==SIG_ERR)
		err_sys("signal error ");

	exit(0);
}



