/*
 * TestMyException.c
 *
 *  Created on: 2016年2月22日
 *      Author: haipinghu
 */
#include <stdio.h>
#include "MyException.h"

void f1();
void f2();
void f3();
void f4();

int
main(){
	My_try{
		printf(" call f1 \n");
		f1();
	}My_catch(err){
		printf("is get error %d\n",err);
	}
}
void f1(){
	printf("call f2 \n");
	f2();
}
void f2(){
	My_try{
		printf(" call f3 \n");
		f3();
	}My_catch(err){
		printf("is get catch err %d ",err);
		My_throw(6);
	}
}

void f3(){
	printf(" call f4 \n");
	My_throw(7);
	f4();
}

void f4(){
	printf(" have not get hear \n");
}



