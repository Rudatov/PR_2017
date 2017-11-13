#include <stdio.h>
#include <stdlib.h>
#include <errno.h>


int main(int argc, char** args[]){
	FILE* f1;
	FILE* f2;
	int ret_rd;
	int ret_wr;
	int nbalire=4096;
	int nblu =0;
	int nbecr=0;
	char* buff[4096]; /*crée un buffer de 4096 octets*/
	if(argc!=3){/*nom_program, fichier1 et fichier2*/
		perror("il faut exactement deux noms de fichier.");
		return errno;
	}
	f1 = fopen(args[1],"r");
	if(f1 == -1 ){
		printf("errno = %d",errno);
		perror("Erreur du premier fichier passé en paramètres.");
		return errno;
	}
	f2 = open(args[2],"w/Create");
	if(f2==-1){
		printf("errno = %d",errno);
		perror("Erreur sur le second fichier passé en paramètres.");
		return errno;
	}

	/*rajouter boucle while*/

	do{
		ret_rd=read(f1,buff,4096);
		nblu+=ret_rd;
	}while((nblu<nbalire)&&(nblu!=0));

	do{
		ret_wr=write(f2,buff,4096);
		nbecr+=ret_wr;
	}while((nbecr<nbalire)&&(nbecr!=0));
	


	return 0;
}