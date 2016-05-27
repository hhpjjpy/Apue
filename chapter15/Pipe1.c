/*
 * Pipe1.c
 *
 *  Created on: 2016年3月14日
 *      Author: haipinghu
 */
#include "apue.h"

int main(void){
	int n;
	int fd[2];
	pid_t pid;
	char line[MAXLINE];

	//bzero((void*)line,sizeof(line));

	if(pipe(fd)<0)
		err_sys(" pipe error ");

	if((pid = fork())<0 ){
		err_sys(" fork error ");
	}else if(pid != 0 ){
		close(fd[0]);
		write(fd[1],"hello world\n",12);
	}else {
		close(fd[1]);
		n = read(fd[0],line,MAXLINE);
		write(STDOUT_FILENO,line,n);
	}

	exit(0);
}



