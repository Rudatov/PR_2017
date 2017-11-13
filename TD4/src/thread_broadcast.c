#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
pthread_mutex_t mutex_pth = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER; 
int flag =0;


void* wait_barrier(void){
	
	while(!flag){
		pthread_cond_wait(&cond,&mutex_pth);
	}
	pthread_exit((void*)0);
}

void* threadProcess(void* arg){
	printf("avant barriere\n");
	wait_barrier();
	printf("apres barriere\n");
	pthread_exit(NULL);
}




int main(int argc, char** args){
	int N = atoi(args[1]);
	int i=0;
	while(i<N){
		pthread_t tid;
		pthread_create(&tid,NULL,threadProcess,(void*)N);
		pthread_join(tid,NULL);
	}
	sleep(1);
	pthread_mutex_lock(&mutex_pth);
	flag=1;
	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&mutex_pth);
	return EXIT_SUCCESS;
}
