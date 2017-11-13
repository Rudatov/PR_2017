#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>

int changedroit(char* fichier,char new_droit);
int renomefich(char* fichier, char* new_name);
int remove_fich(char* fichier);

int main(int argc,char** argv){
	char type_op;
	int retour=EXIT_SUCCESS;

	type_op=*argv[1];
	switch(type_op){
		case 'E':
		case 'e':
			remove_fich(argv[2]);
			printf("fin rm fichier\n");
			break;
		case 'R':
		case 'r':
			renomefich(argv[2],argv[3]);
			printf("fin rename fichier \n");
			break;
		case 'C':
		case 'c':
			changedroit(argv[2],*argv[3]);
			printf("fin changedroits \n");
			break;
		default:
			perror("erreur main\n");
			retour=errno;
			break;
	}

	return retour;
}



int changedroit(char* fichier,char new_droit){
	int ret=EXIT_SUCCESS;
	switch(new_droit){
		case 'R':
		case 'r':
			chmod(fichier,S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
			break;

		case 'W':
		case 'w':
			chmod(fichier,S_IRUSR|S_IWUSR|S_IWGRP|S_IWOTH);
			break;

		default:
			perror("erreur changedroits\n");
			ret=errno;
			break;
	}
	return ret;
}

int renomefich(char* fichier, char* new_name){
	if(rename(fichier,new_name)!=0){
		perror("probleme de renomage\n");
		return errno;
	}
	return EXIT_SUCCESS;

}


int remove_fich(char* fichier){
	if(unlink(fichier)==-1){
		perror("probleme de suppression \n");
		return errno;
	}
	return EXIT_SUCCESS;
}