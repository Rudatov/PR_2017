//thread_rand.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_mutex_t* mutex_pth;

void* threadProcess(void *arg){
	
	int* alea_test ;
	*alea_test = (int) (10*((double)rand())/ RAND_MAX);
	int* arg_test = (int*) arg;
	pthread_t thread_tmp= pthread_self();
	
	pthread_mutex_lock(mutex_pth);
	
	*arg_test += *alea_test;
	printf("%d | %d | %d\n",*arg_test,*alea_test,(int)thread_tmp);
	
	pthread_mutex_unlock(mutex_pth);
	pthread_exit(arg);
	return 0;
}

int main(int argc, char** args){
	if(argc!=2){
		perror("erreur de saisie des arguments\n");
		return -1;
	}
	mutex_pth=PTHREAD_MUTEX_INITIALIZER;
	pthread_mutex_init(mutex_pth,NULL);
	int* retour;
	retour = 0;
	int  N = atoi(args[1]);
	int *ret[N];
	pthread_t tab_id[N];
	for(int i=0;i<N;i++){
		if(pthread_create(&tab_id[i],NULL,threadProcess,&retour)<0){
			perror("erreur de creation de thread \n ");
			return -1;
		}
		printf("%d\n",i);
	}
	for(int j=0;j<N;j++){
		pthread_join(tab_id[j],&ret[j]);
		printf("%d\n",*ret[j]);
	}
	return 0;
}

