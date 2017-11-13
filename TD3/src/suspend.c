//suspend.c
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>



//signal SIGCHLD --> un fils est mort
//meme structure code que chaine_proc 
void handler(int signal){
	printf("\n");
}

int main(int argc,char** args){
	if(argc != 2 ){
		perror("Probleme d'argument\n");
		return -1;
	}
	int N = atoi(args[1]);
	//int N=10;
	pid_t pids[N];
	pids[0]=getpid();
	int exit_val,i;
	sigset_t test_set;
//1. chaine de proc
//2. passer le pid
//3. quel code ?
	sigfillset(&test_set);
	sigdelset(&test_set,SIGCHLD);
	for(i=0;i<N;i++){
		int p=fork();
		if(p==-1){
			perror("erreur fork \n");
			exit(errno);
		}//perror
		if(p!=0){
			pids[i+1]=p;
			break;
		}else{
			pids[i+1]=getpid();

		}
	}
	sleep(1);
	if(i==N){
//Final
//impression de tous les pids
		for(int j=0;j<=N;j++){
			if(j==N){
				printf("%d",pids[j]);
			}else{
				printf("%d | ",pids[j]);
			}
		}
		printf("\n");
		
		exit(0);
	}
	else{
//intermediaire et pere
//impression pid pere/soi-meme/fils
		struct sigaction sa;
		sa.sa_handler = handler;
		sigaction(SIGCHLD,&sa,NULL);
		sigsuspend(&test_set);

		printf("Pere : %d | Self : %d | Fils : %d \n",pids[i-1],getpid(),pids[i+1]);
		
		exit(WEXITSTATUS(exit_val));
	}
	return 0;
}
