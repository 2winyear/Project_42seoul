#ifndef MICRO_H
#define MICRO_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct  s_paint {
    int height;
    int width;
    char print;
    char *data_arr;
}               t_paint;

typedef struct  s_rect {
    float x;
    float y;
    float xd;
    float yd;
    char type;
    char print;
}               t_rect;

#endif