#include "push_swap.h"

t_Pushswap	*push_swap_init(void)
{
	t_Pushswap	*ret;

	ret = (t_Pushswap *)malloc(sizeof(t_Pushswap));
	if (ret == NULL)
		return (NULL);
	ret->count = 0;
	return (ret);
}

int	sa(t_Stack *a, int ss)
{
	t_element	m;
	t_element	n;

	if (size(*a) < 2)
		return (0);
	if (ss == 0)
		write(1, "sa\n", 3);
	m = pop_head(a);
	n = pop_head(a);
	push_head(a, m);
	push_head(a, n);
	return (1);
}

int	sb(t_Stack *b, int ss)
{
	t_element	m;
	t_element	n;

	if (size(*b) < 2)
		return (0);
	if (ss == 0)
		write(1, "sb\n", 3);
	m = pop_head(b);
	n = pop_head(b);
	push_head(b, m);
	push_head(b, n);
	return (1);
}

int	ss(t_Stack *a, t_Stack *b)
{
	if (size(*a) == 0)
		return (0);
	if (size(*b) == 0)
		return (0);
	write(1, "ss\n", 3);
	sa(a, 1);
	sb(b, 1);
	return (1);
}

int	pa(t_Stack *a, t_Stack *b)
{
	t_element	item;

	if (IsEmpty(*b))
		return (0);
	write(1, "pa\n", 3);
	item = pop_head(b);
	push_head(a, item);
	return (1);
}
