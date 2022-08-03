#ifndef MINI_PAINT
# define MINI_PAINT

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

# define ERROR -1;

typedef struct  s_zone
{
    int width;
    int height;
    char char_to_print;
    char *data_arr;
}               t_zone;

typedef struct  s_circle
{
    char type;
    float x;
    float y;
    float radius;
    char char_to_print;
}               t_circle;

#endif