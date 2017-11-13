//stop_and_go.c
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
	kill(getpid(),SIGSTOP);
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
	int i;
	sigset_t test_set;
//1. chaine de proc
//2. passer le pid
//3. quel code ?
	sigfillset(&test_set);
	sigdelset(&test_set,SIGCHLD);
	int p;
	for(i=0;i<N;i++){
		p=fork();
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
	if(getpid()==pids[0]){// si c'est le pere
		sigsuspend(SIGCHLD);
		printf("tous les processus sont suspendus \n");
		kill(pids[1],SIGCONT);
		
		

	}
	else {
//intermediaire et final
//impression pid pere/soi-meme/fils
		struct sigaction sa;
		sa.sa_handler = handler;
		sigaction(SIGCHLD,&sa,NULL);
		
		if(i!=N){
			printf("Pere : %d | Self : %d | Fils : %d \n",pids[i-1],getpid(),pids[i+1]);
			kill(pids[i+1],SIGCONT);
		}else{
			printf("dernier fils continue et va se terminer \n");
		}
		
		
	}
	return 0;
}



//dernier 
// utiliser handler(SIG);
///proccessus fils autostop , -> kill(getpid(),SIGSTOP); // renvois de SIGCHLD
//proc intermed sautokill quand recoit SIGCHLD
// pere recoit SIGCHILD fais affichage et debloque son fils direct qui va debloquer le sien et ainsi de suite
//handle --> SIGCHLD : se stopper |||| si pere SIGCONT sur fils
//attente :
//body intermed :
//	sigsuspend(SIGCHLD);
////	kill(fils,SIGCONT);
	//exit(0);

	//pour handler  sa_action , pointeur de fonction

	//creer var globale pour reconnaitre pere intial , handler fonction hors du main.