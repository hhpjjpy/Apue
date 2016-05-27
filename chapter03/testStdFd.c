/*
 * testStdFd.c
 *
 *  Created on: 2016年2月19日
 *      Author: haipinghu
 */
#include "apue.h"

int
main(void){
	if(lseek(STDIN_FILENO,0,SEEK_CUR) == -1)//某些设备允许返回负的文件偏移量，所以此处比较应该为 ＝＝ －1.
		printf(" set offset is error \n");
	else
		printf(" set offset is ok \n");

	exit(0);
}



