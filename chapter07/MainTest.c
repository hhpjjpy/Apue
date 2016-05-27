/*
 * MainTest.c
 *
 *  Created on: 2016年2月21日
 *      Author: haipinghu
 */
#include "apue.h"

void my_exit1(){
	printf(" my exit have exec 111 \n");
}
void my_exit2(){
	printf(" my exit have exec 222 \n");
}
/*
 * atexit 登记顺序与执行（调用）顺序相反
 */
int
main(int argc,char *argv[]){
	int i = 0;
	for(;i<argc;i++)
		printf("%s \n",argv[i]);

	if(atexit(my_exit1) != 0)
		err_sys(" atexit is error ");

	if(atexit(my_exit2)!=0)
		err_sys(" atexit is error ");

	exit(0);
}



