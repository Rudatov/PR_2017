//client_maj.c
/*



uperfrompstream (int fd){
	while read
		write
}

int copyStream(int fdr, int fdw){
	//meme que upperFromStream
}
*/
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

int main(int argc, char** args){
	char* nomtube = args[1];
	int fd = open(nomtube,O_WRONLY);
	char test_in;
	while(1){
		if(read(STDIN_FILENO,&test_in,1)==-1){
			perror("erreur lecture\n");
			return errno;
		}else if(write(fd,&test_in,1)==-1){
			perror("erreur ecriture\n");
			return errno;
		}
	}

	return 0;
}