#ifndef MINI
# define MINI

#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct  s_mine
{
    int width;
    int height;
    char *char_arr;
    char char_to_print;
}               t_mine;

typedef struct  s_circle
{
    float x;
    float y;
    float radius;
    char type;
    char char_to_print;
}               t_circle;

#endif
