/*
 * unix_xsi.c
 *
 *  Created on: 2016年4月1日
 *      Author: haipinghu
 */
#include "apue.h"
#include <poll.h>
#include <pthread.h>
#include <sys/msg.h>
#include <sys/socket.h>

#define NQ 3
#define MAXMSZ 512
#define KEY 0x123

struct threadinfo{
	int qid;
	int fd;
};

struct mymesg{
	long mtype;
	char mtext[MAXMSZ];
};

void*
helper(void *arg)
{
	int n;
	struct mymesg   m;

	struct threadinfo *tip = arg;

	for(;;){
		memset(&m,0,sizeof(m));
		if((n=msgrcv(tip->qid,&m,MAXMSZ,0,MSG_NOERROR)) < 0)
			err_sys("msgrcv error ");
	}
}





