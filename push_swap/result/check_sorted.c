#include "push_swap.h"

int	check_sorted(t_Stack *a, int cnt)
{
	t_ListNode	*ptr;
	int			num;

	if (size(*a) < 2)
		return (TRUE);
	ptr = a->head;
	num = cnt;
	while (ptr->prev && num != 0)
	{
		if (ft_atoi(ptr->data) > ft_atoi(ptr->prev->data))
			return (FALSE);
		ptr = ptr->prev;
		num--;
	}
	return (TRUE);
}

int	check_reverse_sorted(t_Stack *b, int cnt)
{
	t_ListNode	*ptr;
	int			num;

	if (size(*b) < 2)
		return (TRUE);
	ptr = b->head;
	num = cnt;
	while (ptr->prev && num != 0)
	{
		if (ft_atoi(ptr->data) < ft_atoi(ptr->prev->data))
			return (FALSE);
		ptr = ptr->prev;
		num--;
	}
	return (TRUE);
}
