//service.c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <ctype.h>


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