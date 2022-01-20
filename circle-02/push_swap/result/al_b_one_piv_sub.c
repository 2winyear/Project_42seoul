#include "push_swap.h"

int	process_at_b_stack(t_Stack *a, t_Stack *b, int *info, int *ret)
{
	t_ListNode	*ptr;
	int			count;

	count = 0;
	ptr = b->head;
	if ((ret[1] == (info[1] - (int)(info[1] / 2) - 1)) \
		&& (ft_atoi(ptr->prev->data) > info[0]))
	{
		sb(a, 0);
		pa(a, b);
		ret[1]++;
		count ++;
	}
	else
	{
		rb(b, 0);
		ret[0]++;
	}
	return (count);
}

int	process_main_b_to_a_one_pivot(t_Stack *a, t_Stack *b, int *info, int *ret)
{
	t_ListNode	*ptr;
	int			count;

	ptr = b->head;
	count = 0;
	if (ft_atoi(ptr->data) > info[0])
	{
		pa(a, b);
		ret[1]++;
	}
	else
		count = process_at_b_stack(a, b, info, ret);
	return (count);
}
