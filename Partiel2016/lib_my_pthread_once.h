#ifndef _MY_PTHREAD_ONCE_H
#define _MY_PTHREAD_ONCE_H

#define _XOPEN_SOURCE 700

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctype.h>
#include <errno.h>

typedef struct{
	char flag;
	pthread_mutex_t mutex_flag;
} my_pthread_once_t;

int my_pthread_once(my_pthread_once_t *once, void *(*to_execute) (void *), void *arg);

void my_pthread_once_t_init(my_pthread_once_t *once);

#endif
