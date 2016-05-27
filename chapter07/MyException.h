/*
 * MyException.h
 *
 *  Created on: 2016年2月22日
 *      Author: haipinghu
 */
#ifndef CHAPTER07_MYEXCEPTION_H_
#define CHAPTER07_MYEXCEPTION_H_
#include <setjmp.h>
#include <stdlib.h>

typedef struct node{
	struct node *next;
	struct node *pre;
	jmp_buf jmpbuffer;
}jmpnode;


int err = -1;
jmpnode *p_now=NULL;

void  addJmp(){
	 jmpnode *newnode = (jmpnode*)malloc(sizeof(jmpnode));
	 if(p_now == NULL){
		 p_now = newnode;
		 p_now ->pre = NULL;
		 p_now ->next = NULL;
	 }else{
		 p_now->next = newnode;
		 newnode->pre = p_now;
		 newnode->next = NULL;
		 p_now = newnode;
	 }
}

void removeLastJmpnode(){
	jmpnode *p_temp=NULL;
	if(p_now==NULL)
		return;
	if(p_now->pre != NULL){
		p_temp = p_now->pre;
	}
	free(p_now);
	p_now = p_temp;
}


void Mylongjmp(){
	longjmp(p_now->jmpbuffer,1);
}

void DestoryJmp(){
	removeLastJmpnode();
}

#define My_try addJmp();if(setjmp(p_now->jmpbuffer) == 0)
#define My_catch(N) DestoryJmp();if(N>0)
#define My_throw(N) err = N;Mylongjmp();



#endif /* CHAPTER07_MYEXCEPTION_H_ */
