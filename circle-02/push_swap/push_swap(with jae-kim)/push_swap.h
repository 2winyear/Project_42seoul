#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include "util.h"
#include "stack_link_list.h"

typedef struct pushswap {
  int count;
} Pushswap;

int check_input_number(char *input, Pushswap *p);
void sa(Stack *a);
void sb(Stack *b);
void ss(Stack *a, Stack *b);
void pa(Stack *a, Stack *b);
void pb(Stack *a, Stack *b);
void ra(Stack *a);
void rb(Stack *b);
void rra(Stack *a);
void rrb(Stack *b);
void rrr(Stack *a, Stack *b);

#endif 