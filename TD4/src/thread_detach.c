/*
Erreur a la compilation, en ligne 39 le printf de la valeur de i dans la premiere boucle s'arrete à 3.

*/


//thread_rand.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
pthread_mutex_t mutex_pth = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER; 

int les_res[3];

void* threadProcess(void*arg){
        
        int alea_test = (int) (10*((double)rand())/ RAND_MAX);
        pthread_t thread_tmp= pthread_self();
        pthread_detach(thread_tmp);
        pthread_mutex_lock(&mutex_pth);
        //section critique
        les_res[2]++;
        
        les_res[0] += alea_test;
        printf("%d\n",alea_test);
        pthread_mutex_unlock(&mutex_pth);
        if(les_res[2]==les_res[1]-1){
            pthread_cond_signal(&cond);
        }
        pthread_exit(arg);
        
        return 0;
}

void* threadAffiche(void* arg){
    
    pthread_cond_wait(&cond, &mutex_pth);
   
    printf("%d\n ", les_res[0]);
    return 0;
}

int main(int argc, char** args){
        if(argc!=2){
                perror("erreur de saisie des arguments\n");
                return -1;
        }
        int* retour;
        les_res[0] = 0;
        les_res[2] = 0;
        int  N = atoi(args[1]);
        les_res[1] = N;
        int *ret[N];
        pthread_t tab_id[N];
        for(int i=0;i<N;i++){
                
                if(i==0){
                    if(pthread_create(&tab_id[i],NULL,threadAffiche,retour)<0){
                        perror("erreur first thread\n");
                        return -1;
                    }
                }
                else if(pthread_create(&tab_id[i],NULL,threadProcess,retour)<0){
                        perror("erreur de creation de thread \n ");
                        return -1;
                }
                if(i==N-1){
                    printf("test 1\n");
                }
                
        }
        printf("%d\n",retour);
        printf("test\n");
        return 0;
}
