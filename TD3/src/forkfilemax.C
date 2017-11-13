//forkfilemax.C
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>


// F1 : write 123 offset
// F2 : write 45 0
// P1 : seek(0)
// P2 : write fg offset
// P3 : write hi offset

//F1, F2, P1, P2, P3 : abcde123
//						45cde123
//						fgcde123
//						fghie123

//F1,P1, F2, P2, P3 :   ~~
//						45cde123
//						fgcde123
//						fghie123

//P1, P2, P3, F1, F2 :  ~~
//						45hi123

//pour avoir toujours au moins 8 char, on doit avoir F1 qui precede P1

//signaler a P quand F1 est fini

/*
Fils : 
write (123 )
kill(pere,usr1)
write (45 offseek_0)

Pere : Sigsuspend(usr1)
		suite code

*/