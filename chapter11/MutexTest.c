/*
 * MutexTest.c
 *
 *  Created on: 2016年3月7日
 *      Author: haipinghu
 */
#include "apue.h"
#include <stdlib.h>
#include <pthread.h>

typedef struct foo{
	int 			f_count;
	pthread_mutex_t f_lock;
	int 			f_id;
} mutexfoo;

mutexfoo* foo_alloc(int id){
	mutexfoo *fp;
	if( (fp=(mutexfoo*)malloc(sizeof(mutexfoo))) != NULL){
		fp->f_count = 1;
		fp->f_id = id;
		if(pthread_mutex_init(&fp->f_lock,NULL) !=0){
			free(fp);
			return NULL;
		}
	}
	return fp;
}

void foo_hold( mutexfoo *fp){
	pthread_mutex_lock(&fp->f_lock);
	fp->f_count ++;
	pthread_mutex_unlock(&fp->f_lock);
}

void foo_rele(mutexfoo *fp){
	pthread_mutex_lock(&fp->f_lock);
	if( --fp->f_count == 0){
		pthread_mutex_unlock(&fp->f_lock);
		pthread_mutex_destroy(&fp->f_lock);
		free(fp);
	}else{
		pthread_mutex_unlock(&fp->f_lock);
	}
}

void fun(const char *thname,mutexfoo *fp){
	foo_hold(fp);
	printf(" thread:%s, fooid: %d ,foo->count is :  %d \n",thname,fp->f_id,fp->f_count);
	foo_rele(fp);
}

void * thread_fun1(void *fp){
	int i=100;
	while(i--){
		fun("thread1",(mutexfoo*)fp);
	}
	return ((void*)0);
}

void * thread_fun2(void *fp){
	int i=100;
	while(i--){
		fun("thread2",(mutexfoo*)fp);
	}
	return ((void*)0);
}



int main(){
	mutexfoo *fp = foo_alloc(12345);
	pthread_t tid1,tid2;

	if(pthread_create(&tid1,NULL,thread_fun1,fp)!=0)
		err_sys("create pthread is error \n");
	if(pthread_create(&tid2,NULL,thread_fun2,fp)!=0)
			err_sys("create pthread is error \n");
	printf("main pthread is sleep \n");
	sleep(10);
	printf("main pthread is wake up \n");
	exit(1);
}




