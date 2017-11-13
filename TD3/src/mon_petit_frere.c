#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main(void){
	int j=0;
	int i=0;
	pid_t p,p2,pid_aine;
	while(i<2){
		p=fork();
		if(p==0){
			if(i==0){
				pid_aine=getpid();
				sigsuspend(SIGUSR1);
				sigsuspend(SIGUSR2);
			}else{

				printf("frere aine %d \n",pid_aine);
				kill(pid_aine,SIGUSR1);
			}
			p2=fork();
			
			if(p2==0){
				printf("%d || %d \n",getpid(),getppid());
				if(i==0){
					kill(pid_aine,SIGUSR2);
				}
				exit(0);
			}
		}
		i++;
	}
}