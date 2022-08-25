#pragma once

#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

typedef struct  s_art
{
    pthread_t   pid;
    char*       art;
    int         fd;
}               t_art;

char*   get_dog_art();
char*   get_cat_art();
void*   commit(void* value);