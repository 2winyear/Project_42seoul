#include "push_swap.h"

int	pb(t_Stack *a, t_Stack *b)
{
	t_element	item;

	if (IsEmpty(*a))
		return (0);
	write(1, "pb\n", 3);
	item = pop_head(a);
	push_head(b, item);
	return (1);
}

int	ra(t_Stack *a, int rr)
{
	t_element	item;

	if (size(*a) < 2)
		return (0);
	if (rr == 0)
		write(1, "ra\n", 3);
	item = pop_head(a);
	push_tail(a, item);
	return (1);
}

int	rb(t_Stack *b, int rr)
{
	t_element	item;

	if (size(*b) < 2)
		return (0);
	if (rr == 0)
		write(1, "rb\n", 3);
	item = pop_head(b);
	push_tail(b, item);
	return (1);
}

int	rr(t_Stack *a, t_Stack *b)
{
	if (size(*a) == 0)
		return (0);
	if (size(*b) == 0)
		return (0);
	write(1, "rr\n", 3);
	ra(a, 1);
	rb(b, 1);
	return (1);
}

int	rra(t_Stack *a, int rrr)
{
	t_element	item;

	if (a->count < 2)
		return (0);
	if (rrr == 0)
		write(1, "rra\n", 4);
	item = pop_tail(a);
	push_head(a, item);
	return (1);
}
