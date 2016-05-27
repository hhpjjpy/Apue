/*
 * CoprocessMain.c
 *
 *  Created on: 2016年3月16日
 *      Author: haipinghu
 */
#include "apue.h"

int main(int argc ,char *argv[]){

	int pfd1[2],pfd2[2];
	pid_t pid;

	if(pipe(pfd1) < 0 )
		err_sys("pipe error");
	if(pipe(pfd2) < 0)
		err_sys("pipe error");
	if( (pid = fork()) < 0 )
		err_sys("fork error ");
	if(pid == 0){
		close(pfd1[1]);
		close(pfd2[0]);
		if(pfd1[0] != STDIN_FILENO){
			if(dup2(pfd1[0],STDIN_FILENO) != STDIN_FILENO)
				err_sys(" dup2 error ");
		}
		if(pfd2[1] != STDOUT_FILENO){
			if(dup2(pfd2[1],STDOUT_FILENO) != STDOUT_FILENO)
				err_sys(" dup2 error ");
		}

		if(execl("./CoprocessSum","sum",(char*)0) < 0)
			err_sys("execle error ");
	}else{
		close(pfd1[0]);
		close(pfd2[1]);
		int n;
		char line[MAXLINE];

		while(fgets(line,MAXLINE,stdin) != NULL){

		if(write(pfd1[1],line,strlen(line)) != strlen(line))
			err_sys("write is error ");

	    if((n=read(pfd2[0],line,MAXLINE))<0){
	    	err_sys("read error");
	    }else{
	    	line[n] = 0;
	    	printf("sum is : %s",line);
	    }

		}

	    if(waitpid(pid,NULL,0)<0)
	    	err_sys("waitpid is error ");

	    exit(0);
	}
}



