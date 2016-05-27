/*
 * fileio3_6.c
 *
 *  Created on: 2016年2月20日
 *      Author: haipinghu
 */
#include "apue.h"
#include "string.h"
#include <fcntl.h>

int
main(void){
	int fd;

	if(creat("file3.6.test",FILE_MODE)<0)
		err_sys(" creat is error \n");

	if( (fd=open("file3.6.test",O_RDWR|O_APPEND,FILE_MODE)) < 0 )
		err_sys(" open is error\n");

	char  writebuf[] = "hello world ";

	if(write(fd,writebuf,sizeof(writebuf))!=sizeof(writebuf))
		err_sys("write error \n");

	lseek(fd,0,SEEK_SET);
	char readbuf[10];
	if(read(fd,readbuf,sizeof(writebuf)) !=0 )
			printf("readbuf is %s \n",readbuf);

	memset(readbuf,0,sizeof(readbuf));

	int off = lseek(fd,0,SEEK_CUR);
	printf("offset is : %d \n",off);

	if((off = lseek(fd,5,SEEK_SET))==-1)
		err_sys("set offset is error \n");

	if(read(fd,readbuf,5) !=0 )
		printf("readbuf is %s \n",readbuf);

	exit(0);

}



