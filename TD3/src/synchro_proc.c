//synchro_proc.c
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>


//1. P2 signaler a P1
//2. P2 kill et envois sigchld
//3. p1 signale p3 mort a p1
//4. p1 se kill
//5. p0 prend conscience de la mort de p2 et affiche


int main(int argc,char** argv){
	int exit_val;
	//sigset_t test_set_usr2;
	//sigset_t test_set_usr1;
	// creer deux set usr ou gerer ordre des sigdelset
	//sigfillset(&test_set_usr2);
	//sigfillset(&test_set_usr1);
	//sigaddset(&test_set_usr1,SIGUSR1);
	//sigaddset(&test_set_usr2,SIGUSR2);
	int p, p2;
	int pid_pere=getpid();
	p=fork();
	if(p!=0){
		sigsuspend(SIGUSR2);
		//affiche p3 mort (usr2)
		printf("YO\n");

		sigsuspend(SIGUSR1);
		//sigsuspend(usr1)
		
		printf("P2 mort\n");
		//affichage p2 mort
	}else{
		
		p2 = fork();
		if(p2!=0){
			wait(&exit_val);
			printf("P3 mort\n");
			kill(pid_pere,SIGUSR1);
			//fils
		}else{
			printf("P3 creer\n");
			kill(pid_pere,SIGUSR2);
			exit(0);
			//petit_fils
		}
	}


	return 0;
}

//P2. kill(p0, USR1)
// 		exit (0);

//P1. sigsuspend(chld) ou wait()
//	  kill (p0,usr2)
//

//P0. Handler USR1 -> afficher P2 mort
//  			USR2 --> afficher p1 mort 
//masquerr usr1 et usr2
//demasquer et sigsuspend usr1
//demasquer et sigsuspend usr2