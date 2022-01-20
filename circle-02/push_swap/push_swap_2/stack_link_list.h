#ifndef LINKED_LIST
# define LINKED_LIST

#include "link_list.h"
#define MAX 10001

typedef struct	_stack
{
	ListNode *head;
	ListNode *tail;
	int	count;
}				Stack;

Stack *init(void);
int size(Stack a);
int IsEmpty(Stack a);
int IsFull(Stack a);
void push_head(Stack *a, element data);
void push_tail(Stack *a, element data);
element pop_head(Stack *a);
element pop_tail(Stack *a);
element peek_head(Stack *a);
element peek_tail(Stack *a);
void print_stack(Stack *a, Stack *b);
void delete_stack(Stack *a);

#endif