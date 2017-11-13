#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


int threadProcess(void *arg){
	int* test = arg;
	pthread_t thread_tmp= pthread_self();
	printf("%d : %d\n",*test,thread_tmp);
	*test= *test * 2;
	pthread_exit(test);
	return 0;
}

int main(int argc, char** args){
	if(argc!=2){
		perror("erreur de saisie des arguments\n");
		return -1;
	}
	int  N = atoi(args[1]);
	int *ret[N];
	pthread_t tab_id[N];
	int tab_index[N];
	for(int i=0;i<N;i++){
		tab_index[i]=i+1;
		if(pthread_create(&tab_id[i],NULL,threadProcess,&tab_index[i])<0){
			perror("erreur de creation de thread \n ");
			return -1;
		}
	}
	for(int j=0;j<N;j++){
		pthread_join(tab_id[j],&ret[j]);
		printf("%d\n",*ret[j]);
	}
	return 0;
}

