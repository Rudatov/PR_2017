

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

int main(int argc, char** args){
	int fd[2];
	pid_t pid_fils;
	if(pipe(fd)!=0){
		perror("erreur pipe \n");
	}
	char test_in;

	if((pid_fils = fork())==-1){
		perror("erreur creation fils \n");
		return errno;
	}
	if(pid_fils == 0){
		upperFromStream(fd[0]);

	}else{

		while(read(STDIN_FILENO,&test_in,1)==1){
			if(write(fd[1],&test_in,1)==-1){
				perror("Erreur ecriture main \n");
				return errno;
			}
		}
	}
	return 0;

}
/*
pipe() -> 2 entiers = fd ->lecture et ecriture
fd initialiser a int[2]

lire, bloquant si buff vide et write bloquant si buff plein

writer : close fd[0]
		write fd[1]

reader : close fd[1]
		read fd[0]

handler singint (close les fd open)

exo 4 : client cat > montube
		serveur utilisant commande shell mkfifo
*/