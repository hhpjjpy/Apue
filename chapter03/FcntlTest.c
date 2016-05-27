/*
 * FcntlTest.c
 *
 *  Created on: 2016年2月20日
 *      Author: haipinghu
 */
#include "apue.h"
#include <fcntl.h>

int
main(int argc,char *argv[]){
	int val;

	if(argc != 2)
		err_sys(" usage: a.out descriptor ");
	if( (val = fcntl(atoi(argv[1]),F_GETFL,0)) < 0 )
		err_sys("fcntl error for fd %d ",atoi(argv[1]));

	printf(" fd is : %d ACCMODE:%d RDONLY:%d \n",val,O_ACCMODE,O_RDONLY);

	switch (val & O_ACCMODE){
	case O_RDONLY:
		printf(" read only\n");
		break;
	case O_RDWR:
		printf("read write\n");
	default:
		printf(" unknow access mode \n");
	}

	if(val & O_APPEND)
		printf(",append ");

	exit(0);
}



