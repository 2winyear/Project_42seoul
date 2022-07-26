#ifndef MINI_H
#define MINI_H

#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct  s_paint {
    int width;
    int height;
    char *data_arr;
    char print;
}               t_paint;

typedef struct  s_circle {
    float x;
    float y;
    float radius;
    char print;
    char type;
}               t_circle;

#endif