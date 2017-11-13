/*
Erreur a la compilation, en ligne 39 le printf de la valeur de i dans la premiere boucle s'arrete à 3.

*/


//thread_rand.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
 pthread_mutex_t mutex_pth = PTHREAD_MUTEX_INITIALIZER;


void* threadProcess(void *arg){
  int * pint = (int *) arg;
        printf("%d arg \n",*pint);
        int alea_test = (int) (10*((double)rand())/ RAND_MAX);
        pthread_t thread_tmp= pthread_self();
       
        pthread_mutex_lock(&mutex_pth);
        //section critique
        
        
        *pint += alea_test;
        printf("%d | %d | %d\n",*pint,alea_test,thread_tmp);
        pthread_mutex_unlock(&mutex_pth);
        pthread_exit(arg);
        return 0;
}

int main(int argc, char** args){
        if(argc!=2){
                perror("erreur de saisie des arguments\n");
                return -1;
        }
        int* retour = malloc(sizeof(int));
        *retour = 0;
        int  N = atoi(args[1]);
        int *ret[N];
        pthread_t tab_id[N];
        for(int i=0;i<N;i++){
                printf("%d retour \n",*retour);
                if(pthread_create(&tab_id[i],NULL,threadProcess,retour)<0){
                        perror("erreur de creation de thread \n ");
                        return -1;
                }
                
        }
        for(int j=0;j<N;j++){
                pthread_join(tab_id[j],&ret[j]);
		
        }
        printf("%d\n",*retour);
        return 0;
}
