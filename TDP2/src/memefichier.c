#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char** argv){
	struct stat les_stats_1;
	struct stat les_stats_2;
	if(argc!=3){
		perror("besoin de deux nom de fichier en argument.\n");
	}
	if(stat(argv[1],&les_stats_1)==-1){
		perror("erreur stats 1 .\n");
		return -1;
	}
	if(stat(argv[2],&les_stats_2)==-1){
		perror("erreur stats 2 .\n");
		return -1;
	}
	if(les_stats_1.st_dev==les_stats_2.st_dev){
		if(les_stats_2.st_ino==les_stats_1.st_ino){
			printf("Les deux fichiers passé en paramètre sont les memes. \n");
		}else{
			printf("st_ino different \n");
		}
	}else{
		printf("st_dev different \n");
	}


	return EXIT_SUCCESS;
}