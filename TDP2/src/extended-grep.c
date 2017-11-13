#define _XOPEN_SOUCE 700

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <errno.h>

#define _POSIX_SOUCE 1
#define TAILLE_PATH 100

char buff_path [TAILLE_PATH];
DIR *pt_Dir;
struct dirent* dirEnt;
/*utilisation fgets*/
int main(int argc,char** argv){
	int fd;
	if(argc != 3 ){
		printf("Nombre d'arguments incorrect.\n");
		return -1;
	}
	
	if (argc ==1 ) {
		/* repertoir courant : obtenir le nom */
		if (getcwd (buff_path, TAILLE_PATH) == NULL ) {
			perror ("erreur getwcd \n");
			exit (1);
		}
	}
	else
		memcpy (buff_path,argv[2],strlen(argv[2]));

	pt_Dir = opendir (buff_path);
	printf("%s \n",argv[2]);
	char buff[1024];
	while ((dirEnt= readdir (pt_Dir)) !=NULL) {
		fd=fopen(dirEnt->d_name,"r");
		while(fgets(buff,sizeof buff,fd)!=NULL){
			if(strstr(buff,argv[1])!=NULL){
				printf("%s\n",dirEnt->d_name);
			}
		}
		//lire ligne par ligne du fichier dirEnt->d_name et verrifier presence de argv[1]
	}
	closedir (pt_Dir);
	return EXIT_SUCCESS;
}