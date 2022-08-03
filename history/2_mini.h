#ifndef MINI_2_H
# define MINI_2_H

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include  <math.h>

typedef struct s_mine {
	int width;
	int height;
	char char_to_print;
	char *data_arr;
}		t_mine;

typedef struct s_circle {
	float x;
	float y;
	float radius;
	char char_to_print;
	char type;
}		t_circle;

#endif
