#include "stack_link_list.h"
#include "stdio.h"

void sa(Stack *a){

    if (size(*a) < 2)
      return;
    write(1, "sa", sizeof("sa"));
    write(1, "\n", sizeof("\n"));
    write(1, "\n", sizeof("\n"));
    element m, n;
    m = pop_head(a);
    n = pop_head(a);
    push_head(a, m);
    push_head(a, n);

}

void sb(Stack *b){


    if (size(*b) < 2)
      return;
    write(1, "sb", sizeof("sb"));
    write(1, "\n", sizeof("\n"));
    write(1, "\n", sizeof("\n"));
    element m, n;
    m = pop_head(b);
    n = pop_head(b);
    push_head(b, m);
    push_head(b, n);
  
}

void ss(Stack *a, Stack *b){


    if (size(*a) < 2)
      return;

    if (size(*b) < 2)
      return;

  write(2, "ss", sizeof("ss"));
  write(1, "\n", sizeof("\n"));
  write(1, "\n", sizeof("\n"));
  sa(a);
  sb(b); 
}


void pa(Stack *a, Stack *b){

    if (size(*b) == 0)
      return;

  write(1, "pa", sizeof("pa"));
  write(1, "\n", sizeof("\n"));
  write(1, "\n", sizeof("\n"));
  if (IsEmpty(*b)){
    return ;
  }
  element item;
  item = pop_head(b);
  push_head(a, item);

}


void pb(Stack *a, Stack *b){

    if (size(*a) == 0)
      return;

  write(1, "pb", sizeof("pb"));
  write(1, "\n", sizeof("\n"));
  write(1, "\n", sizeof("\n"));
  if (IsEmpty(*a)){
    return ;
  }
  element item;
  item = pop_head(a);
  push_head(b, item);

}

void ra(Stack *a){

    if (size(*a) == 0)
      return;

  write(2, "ra", sizeof("ra"));
  write(1, "\n", sizeof("\n"));
  write(1, "\n", sizeof("\n"));
  if(a->count < 2)
    return ;
  element item;
  item = pop_head(a);
  push_tail(a, item);

}

void rb(Stack *b) {

    if (size(*b) == 0)
      return;
  write(1, "rb", sizeof("rb"));
  write(1, "\n", sizeof("\n"));
  write(1, "\n", sizeof("\n"));
  if(b->count < 2)
    return ;
  element item;
  item = pop_head(b);
  push_tail(b, item);
}

void rr(Stack *a, Stack *b){

    if (size(*a) == 0)
      return;

    if (size(*b) == 0)
      return;

  write(1, "rr", sizeof("rr"));
  write(1, "\n", sizeof("\n"));
  write(1, "\n", sizeof("\n"));
  ra(a);
  rb(b);
}

void rra(Stack *a){


  if (size(*a) == 0)
      return;
  write(1, "rra", sizeof("rra"));
  write(1, "\n", sizeof("\n"));
  write(1, "\n", sizeof("\n"));
  if(a->count < 2)
    return ;
  element item;
  item = pop_tail(a);
  push_head(a, item);
}

void rrb(Stack *b){
    if (size(*b) == 0)
      return;
  write(1, "rrb", sizeof("rrb"));
  write(1, "\n", sizeof("\n"));
  write(1, "\n", sizeof("\n"));
  if(b->count < 2)
    return ;
  element item;
  item = pop_tail(b);
  push_head(b, item);

}

void rrr(Stack *a, Stack *b){
    if (size(*a) == 0)
      return;

    if (size(*b) == 0)
      return;
  write(3, "rrr", sizeof("rrr"));
  write(1, "\n", sizeof("\n"));
  write(1, "\n", sizeof("\n"));
  rra(a);
  rrb(b);
}