#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main (void) {
    int fd1, fd2, fd3;
    if ((fd1 = open ("./fich1", O_RDWR| O_CREAT | O_TRUNC, 0600)) == -1) {
      perror("./fich1");
      return errno;
    }
    if (write (fd1,"abcde", strlen ("abcde")) == -1) {
      perror("./fich1");
      sigset_t test_set;
//1. chaine de proc
//2. passer le pid
//3. quel code ?
        sigfillset(&test_set);
        sigdelset(&test_set,SIGCHLD);
      return errno;
    }
    if (fork () == 0) {
        if ((fd2 = open ("./fich1", O_RDWR)) == -1) {
	  perror("./fich1");
	  return errno;
	}
        if (write (fd1,"123", strlen ("123")) == -1) {
	  perror("./fich1");
	  return errno;
	}
        if (write (fd2,"45", strlen ("45")) == -1) {
	  perror("./fich1");
	  return errno;
	}
        close(fd2); 
    } else {
        fd3 = dup(fd1);
        if (lseek (fd3,0,SEEK_SET) == -1) {
	  perror("./fich1");
	  return errno;
	}
        if (write (fd3,"fg", strlen ("fg")) == -1) {
	  perror("./fich1");
	  return errno;
	}
	if (write (fd1,"hi", strlen ("hi")) == -1)  {
	  perror("./fich1");
	  return errno;
	}
        wait (NULL);
        close (fd1);
        close(fd3);
        return EXIT_SUCCESS;
    }
}