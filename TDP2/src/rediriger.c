#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <fcntl.h>


int main(int argc, char** argv){
	int fd;
	int i=3;
	char* le_char;
	if((fd=open(argv[1],O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH))==-1){
		perror("probleme creation fichier\n");
		return errno;
	}

	while(i<argc){
		printf("%d\n",i);
		if(i==argc-1){
			le_char="\n";
		}else{
			le_char=" ";
		}
		if((write(fd,argv[i],strlen(argv[i])))==-1){
			perror("erreur ecriture 1\n");
			return errno;
		}
		if((write(fd,le_char,1))==-1){
			perror("erreur ecriture 2\n");
			return errno;
		}
		i++;
	}
	char buff[10];
	int ii = 0;
	lseek(fd,0,SEEK_SET);
	
	do{
		if(read(fd,buff,1)==-1){
			perror("probleme lecture\n");
			return errno;
		}
		printf("%c",buff);
	} while(buff!=' ' && ++ii < 10);
	
	if(write(fd,argv[2],strlen(argv[2]))==-1){
		perror("probleme reecriture\n");
		return errno;
	}
	return EXIT_SUCCESS;

}

