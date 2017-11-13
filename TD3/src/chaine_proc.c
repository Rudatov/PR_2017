#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc,char** args){
	if(argc != 2 ){
		perror("Probleme d'argument\n");
		return -1;
	}
	int N = atoi(args[1]); //recuperation nombre de processus a creer en argument
	pid_t pids[N]; //creation d'un tableau de stockage des pid pour chaque proc
	pids[0]=getpid();//premier pid est celui du pere
	int exit_val,i; 
//1. chaine de proc
//2. passer le pid
//3. quel code ?
	int p;
	for(i=0;i<N;i++){
		p=fork(); //creation d'un fils
		if(p==-1){
			perror("erreur fork \n");
			exit(errno);
		}//perror
		if(p!=0){ //si ce n'est pas le pere
			pids[i+1]=p; //on ajoute le pid dans le tableau
			break;
		}else{
			pids[i+1]=getpid(); //sinon on ajoute le pid courrant dans le tableau
		}
	}
	if(getpid()==pids[0]){//si on retrouve le pid du pere
//Pere
		wait(&exit_val);//attente d'une valeur de retour
		printf("aleatoire : %d \n",exit_val);//impression de la valeur aleatoire
		exit(0);//fin de programme

	}else if(i==N){ //sinon si on est le dernier fils
//Final
//impression de tous les pids
		for(int j=0;j<N;j++){ //boucle d'impression
			if(j==N-1){
				printf("%d",pids[j]);
			}else{
				printf("%d | ",pids[j]);
			}
		}
		printf("\n");
		int le_random;
		le_random=(int)(rand()/(((double)RAND_MAX + 1)/100)); //creation d'une valeur aleatoire
		exit(le_random);//retour de la valeur 
	}
	else{
//intermediaire
//impression pid pere/soi-meme/fils
		
		printf("Pere : %d | Self : %d | Fils : %d \n",pids[i-1],getpid(),pids[i+1]);
		wait(&exit_val);
		exit(WEXITSTATUS(exit_val));
	}
	return 0;
}
