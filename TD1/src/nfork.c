#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#define _XOPEN_SOURCE 700


int nfork( int n ) {
    int i = 0; /*nombre de fils crées*/
    int j = 0; /*compteur pour les wait*/ 
    int pid;
    for(i=0;i<n;i++){
        pid = fork();
        if(pid==0){ /*le processus courant est un fils*/
            printf("processus fils %d se meurt\n", getpid());
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
    printf("C'est la fin du père de pid  : %d\n",getpid());
    return i;
}

/*exemple*/
int main(int argc,char** args){
    nfork(3);
    return 0;
}