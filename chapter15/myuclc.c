/*
 * myuclc.c
 *
 *  Created on: 2016年3月15日
 *      Author: haipinghu
 */
#include "apue.h"
#include <ctype.h>

int main(void){
	int c;
	while( (c= getchar()) != EOF){
		if(isupper(c))
			c = c-56;
		if(putchar(c) == EOF)
			err_sys("output error ");
		if(c == '\n')
			fflush(stdout);
	}

	exit(0);
}



