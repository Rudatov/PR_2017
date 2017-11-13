#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>


int main (int argc,char* args[]){
	int i = 0; /*nombre de fils crées*/
    int j = 0; /*compteur pour les wait*/ 
    int pid;
    int sum=0;
    int n = atoi(args[1]);
    printf("will create %d sons\n", n );
    FILE* fd1 = fopen(args[2],"w+");
    if (! fd1) {
    	perror("probleme ouverture");
    	printf("cannot open %s\n", args[2] );
    	exit(1);
    }
    for(i=0;i<n;i++){
        pid = fork();
        if(pid==0){ /*le processus courant est un fils*/
            int new_rand = (int) (10*(float)rand()/ RAND_MAX);
            printf("%d\n",new_rand );
            fprintf(fd1,"%d",new_rand);
            exit(0);
        }
        else if (pid == -1 ) { /*erreur lors du fork(), terminaison de la boucle de creation*/
            printf("Nombre de fils déjà crée : %d .\n",i);
            perror("Erreur du fork.\n ");
            if(i==0){/*si aucun fils n'as été crée  on retourne la valeur 0*/
                i=-1; 
            }
            break;
        }
    }   
    while(j<i){ /* attente de tous les fils*/
         j++;
         wait(0);
    }
    int tmp_char;
    lseek(fd1,0,SEEK_SET);

    while(1){
        if(feof(fd1)){
            break;
        }
        printf("hey\n");
        tmp_char=fgetc(fd1);
        sum+=tmp_char;
    }
    fclose(fd1);
    printf("%d\n",sum );
    return sum;
}