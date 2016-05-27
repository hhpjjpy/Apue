/*
 * devoid_of_content.c
 *
 *  Created on: 2016年2月19日
 *      Author: haipinghu
 */
#include "apue.h"
#include <fcntl.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int
main(void){
	int fd;
	if( (fd = creat("file.hole",FILE_MODE))  <0 )
		err_sys(" create error ");
	if(write(fd,buf1,10) != 10)
		err_sys(" buf1 write error ");
	int off_t = lseek(fd,0,SEEK_CUR);
		printf("1now offset is %d \n",off_t);
	off_t = lseek(fd,16000,SEEK_CUR);
		printf("2now offset is %d \n",off_t);
	if(write(fd,buf2,10) != 10)
		err_sys(" write buf2 is error ");
	off_t = lseek(fd,0,SEEK_CUR);
			printf("1now offset is %d \n",off_t);
	char readbuf[10];
//read test
	fd = open("file.hole",O_RDWR,FILE_MODE);

	while(read(fd,readbuf,10)!=0){
		printf("read info is : %s\n",readbuf);
	}
    exit(0);
}




