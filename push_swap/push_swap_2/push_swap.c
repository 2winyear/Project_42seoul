#include "push_swap.h"

Pushswap	*push_swap_init(void)
{
	Pushswap	*ret;

	if (!(ret = (Pushswap *)malloc(sizeof(Pushswap))))
		return (NULL);
	ret->count = 0;
	return (ret);
}

int	sa(Stack *a, int ss)
{
	element	m;
	element	n;

	if (size(*a) < 2)
		return (0);
	if (ss == 0)
		write(1, "sa\n", sizeof("sa\n"));
	m = pop_head(a);
	n = pop_head(a);
	push_head(a, m);
	push_head(a, n);
	return (1);
}

int	sb(Stack *b, int ss)
{
	element	m;
	element	n;

	if (size(*b) < 2)
		return (0);
	if (ss == 0)
		write(1, "sb\n", sizeof("sb\n"));
	m = pop_head(b);
	n = pop_head(b);
	push_head(b, m);
	push_head(b, n);
	return (1);
}

int	ss(Stack *a, Stack *b)
{
	if (size(*a) == 0)
		return (0);
	if (size(*b) == 0)
		return (0);
	write(1, "ss\n", sizeof("ss\n"));
	sa(a, 1);
	sb(b, 1);
	return (1);
}

int	pa(Stack *a, Stack *b)
{
	element	item;

	if (IsEmpty(*b))
		return (0);
	write(1, "pa\n", sizeof("pa \n"));
	item = pop_head(b);
	push_head(a, item);
	return (1);
}

int	pb(Stack *a, Stack *b)
{
	element	item;

	if (IsEmpty(*a))
		return (0);
	write(1, "pb\n", sizeof("pb\n"));
	item = pop_head(a);
	push_head(b, item);
	return (1);
}

int	ra(Stack *a, int rr)
{
	element	item;

	if (size(*a) < 2)
		return (0);
	if (rr == 0)
		write(1, "ra\n", sizeof("ra\n"));
	item = pop_head(a);
	push_tail(a, item);
	return (1);
}

int	rb(Stack *b, int rr)
{
	element	item;

	if (size(*b) < 2)
		return (0);
	if (rr == 0)
		write(1, "rb\n", sizeof("rb\n"));
	item = pop_head(b);
	push_tail(b, item);
	return (1);
}

int	rr(Stack *a, Stack *b)
{
	if (size(*a) == 0)
		return (0);
	if (size(*b) == 0)
		return (0);
	write(1, "rr\n", sizeof("rr\n"));
	ra(a, 1);
	rb(b, 1);
	return (1);
}

int	rra(Stack *a, int rrr)
{
	element	item;

	if (a->count < 2)
		return (0);
	if (rrr == 0)
		write(1, "rra\n", sizeof("rra\n"));
	item = pop_tail(a);
	push_head(a, item);
	return (1);
}

int	rrb(Stack *b, int rrr)
{
	element	item;

	if (b->count < 2)
		return (0);
	if (rrr == 0)
		write(1, "rrb\n", sizeof("rrb\n"));
	item = pop_tail(b);
	push_head(b, item);
	return (1);
}

int	rrr(Stack *a, Stack *b)
{
	if (size(*a) == 0)
		return (0);
	if (size(*b) == 0)
		return (0);
	write(1, "rrr\n", sizeof("rrr\n"));
	rra(a, 1);
	rrb(b, 1);
	return (1);
}
