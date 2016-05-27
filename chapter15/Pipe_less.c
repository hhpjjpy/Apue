/*
 * Pipe_less.c
 *
 *  Created on: 2016年3月14日
 *      Author: haipinghu
 */
#include "apue.h"
#include <sys/wait.h>

#define DEF_PAGER  "/bin/more"

int main(int argc,char *argv[]){
	int n;
	int fd[2];
	char line[MAXLINE];
	pid_t pid;
	char *pager,*argv0;
	FILE *fp;

	if(argc != 2)
		err_quit("usage: a.out <pathname>");
	if( (fp = fopen(argv[1],"r")) == NULL )
		err_sys("can't open %s ",argv[1]);
	if(pipe(fd)<0)
		err_sys(" pipe is error ");

	if( (pid = fork()) < 0){
		err_sys("fork is error ");
	}else if(pid != 0){
		close(fd[0]);
		while(fgets(line,MAXLINE,fp) == NULL){
			n = strlen(line);
			if(write(fd[1],line,n)!=n)
				err_sys("write is error");
		}
		if(waitpid(pid,NULL,0) < 0 )
			err_sys("waitpid error ");

	}else{
		close(fd[1]);
		if(fd[0] != STDIN_FILENO ){
			if(dup2(fd[0],STDIN_FILENO) != STDIN_FILENO)
				err_sys("dup2 error to stdin ");
			close(fd[0]);
		}
		if( (pager = getenv("PAGER")) == NULL)
			pager = DEF_PAGER;
		if( (argv0 = strrchr(pager,'/')) != NULL)
			argv0++;
		else
			argv0 = pager;
		if(execl(pager,argv0,(char*)0) < 0 )
			err_sys("execl error for %s ",pager);
	}
}



