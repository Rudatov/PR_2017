#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <fcntl.h>
#include "service.h"


char* pathname;
pid_t pid_main;
//variable globale pour pathyname pour handler
int handleInterrupt(){
	close((int)pathname);
	unlink(pathname);
	kill(pid_main,SIGKILL);
	//fermer le tube
	return 0;
}

int upperFromStream(int fd){
	char buff;

	while(read(fd,&buff,1)==1){
		buff = toupper(buff);
		if(write(STDOUT_FILENO, &buff,1)==-1){
			perror("Erreur ecriture upperFromStream\n");
			return errno;
		}
//		printf("%c",buff);
	}
	
	return 0;

}

int main(int argc,char **args){
	pid_main=getpid();
	int entreeTube;
	char test_in;
	pathname=args[1];
	struct sigaction sa;
	sa.sa_handler = handleInterrupt;
	sigaction(SIGINT,&sa,NULL);

	if(mkfifo(args[1],S_IWUSR | S_IRUSR)==-1){
		perror("erreur creation pipe nommée\n");
		return errno;
	}
	if((entreeTube=open(args[1],O_RDONLY))==-1){
		perror("erreur ouverture du tube\n");
		return errno;
	}

	if(read(entreeTube,&test_in,1)==-1){
		perror("erreur lecture serveur \n");
	}else{
			upperFromStream(entreeTube);
	}
	
	return 0;

	//catch signal SIGINT et ferme le tube 
}