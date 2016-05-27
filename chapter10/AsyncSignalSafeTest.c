/*
 * AsyncSignalSafeTest.c
 *
 *  Created on: 2016年2月28日
 *      Author: haipinghu
 */
#include "apue.h"
#include <pwd.h>

static void my_alarm(int signo){
	struct passwd *rootptr;

	printf(" in signal handler \n");
	if( (rootptr = getpwnam("root"))==NULL)
		err_sys(" getpwnam(root) is error ");
	printf("call my_alarm success \n");
}

int
main(void){
	struct passwd *ptr;

	signal(SIGALRM,my_alarm);
	alarm(1);
	for( ; ; ){
		if( (ptr = getpwnam("huhaiping"))==NULL)
			err_sys(" getpwnam(sar) is error ");
		if(strcmp(ptr->pw_name,"sar") !=0 )
			printf(" return value corrupted! pw_name = %s \n",ptr->pw_name);
	}
}





