#include "push_swap.h"

int	rrb(t_Stack *b, int rrr)
{
	t_element	item;

	if (b->count < 2)
		return (0);
	if (rrr == 0)
		write(1, "rrb\n", 4);
	item = pop_tail(b);
	push_head(b, item);
	return (1);
}

int	rrr(t_Stack *a, t_Stack *b)
{
	if (size(*a) == 0)
		return (0);
	if (size(*b) == 0)
		return (0);
	write(1, "rrr\n", 4);
	rra(a, 1);
	rrb(b, 1);
	return (1);
}
