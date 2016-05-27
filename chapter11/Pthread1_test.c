/*
 * Pthread1_test.c
 *
 *  Created on: 2016年3月2日
 *      Author: haipinghu
 */
#include "apue.h"
#include <pthread.h>

pthread_t ntid;

void printids(const char *s ){
	pid_t pid;
	pthread_t tid;

	pid = getpid();
	tid = pthread_self();

	printf(" %s pid : %ld tid : %ld (0x %lx)\n",s,(long)pid,(unsigned long)tid,(unsigned long)tid);
}

void * thr_fun(void *arg){
	printids(" new thread ");
	return ((void*)0);
}

int
main(void){
	int err;

	err = pthread_create(&ntid,NULL,thr_fun,NULL);
	if(err != 0)
		err_exit(err," can't create thread \n");
	printids(" main thread ");
	sleep(5);
	exit(0);
}



