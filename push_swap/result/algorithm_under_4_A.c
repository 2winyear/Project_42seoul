#include "push_swap.h"

static void	sort_sa_A(t_Stack *a, t_Pushswap *p)
{
	t_ListNode	*ptr;

	ptr = a->head;
	if (ft_atoi(ptr->data) > ft_atoi(ptr->prev->data))
	{
		sa(a, 0);
		p->count++;
	}
}

static void	sort_at_3_A(t_Stack *a, int cnt, t_Pushswap *p)
{
	t_ListNode	*ptr;

	ptr = a->head->prev;
	if (size(*a) == cnt)
	{
		if (ft_atoi(ptr->prev->data) < ft_atoi(ptr->data))
		{
			rra(a, 0);
			p->count++;
		}
	}
	else
	{
		if (ft_atoi(ptr->prev->data) < ft_atoi(ptr->data))
		{
			ra(a, 0);
			sa(a, 0);
			rra(a, 0);
			p->count += 3;
		}
	}
	sort_sa_A(a, p);
}

static void	sort_over_2_A(t_Stack *a, int cnt, t_Pushswap *p)
{
	t_ListNode	*ptr;

	ptr = a->head;
	if (ft_atoi(ptr->prev->data) < ft_atoi(ptr->data))
	{
		sa(a, 0);
		p->count++;
	}
	if (cnt == 3)
	{
		sort_at_3_A(a, cnt, p);
		ptr = a->head;
		if (ft_atoi(ptr->data) > ft_atoi(ptr->prev->data))
		{
			sa(a, 0);
			p->count++;
		}
	}
}

void	sort_under_4_A(t_Stack *a, int cnt, t_Pushswap *p)
{
	if (check_sorted(a, cnt))
		return ;
	if (cnt >= 2)
		sort_over_2_A(a, cnt, p);
}
