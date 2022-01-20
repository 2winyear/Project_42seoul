#ifndef STACK_LINK_LIST_H
# define STACK_LINK_LIST_H

# include "link_list.h"
# define MAX 10001

typedef struct s_Stack
{
	t_ListNode	*head;
	t_ListNode	*tail;
	int			count;
}				t_Stack;

t_Stack			*init(void);
int				size(t_Stack	a);
int				IsEmpty(t_Stack	a);
int				IsFull(t_Stack a);
void			push_head(t_Stack	*a, t_element	data);
void			push_tail(t_Stack	*a, t_element	data);
t_element		pop_head(t_Stack	*a);
t_element		pop_tail(t_Stack	*a);
t_element		peek_head(t_Stack	*a);
t_element		peek_tail(t_Stack	*a);
void			print_stack(t_Stack	*a, t_Stack	*b);
void			delete_stack(t_Stack	*a);
#endif
