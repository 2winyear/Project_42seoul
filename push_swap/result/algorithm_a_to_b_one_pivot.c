#include "push_swap.h"

int	process_at_a_stack(t_Stack *a, t_Stack *b, int *info, int *ret)
{
	t_ListNode	*ptr;
	int			count;

	count = 0;
	ptr = a->head;
	if ((ret[1] == (info[1] - (int)(info[1] / 2) - 1)) \
		&& (ft_atoi(ptr->prev->data) < info[0]))
	{
		sa(a, 0);
		pb(a, b);
		ret[1]++;
		count ++;
	}
	else
	{
		ra(a, 0);
		ret[0]++;
	}
	return (count);
}

int	process_main_a_to_b_one_pivot(t_Stack *a, t_Stack *b, int *info, int *ret)
{
	t_ListNode	*ptr;
	int			count;

	count = 0;
	ptr = a->head;
	if (ft_atoi(ptr->data) < info[0])
	{
		pb(a, b);
		ret[1]++;
	}
	else
		count = process_at_a_stack(a, b, info, ret);
	return (count);
}

static int	check_partition(t_Stack *a, int cnt, int *cur_cnt)
{
	int		part;
	int		ret;
	int		i;

	i = 0;
	part = TRUE;
	ret = 0;
	if (size(*a) == cnt)
		part = FALSE;
	if (part == TRUE)
	{
		while (i < cur_cnt[0])
		{
			rra(a, 0);
			ret++;
			i++;
		}
	}
	return (ret);
}

int	process_a_to_b_one(t_Stack *a, t_Stack *b, int cnt, int *cur_cnt)
{
	int		info[2];
	int		count;

	count = 0;
	info[1] = cnt;
	info[0] = get_middle_pivot(a, cnt);
	while (cnt != 0)
	{
		count += process_main_a_to_b_one_pivot(a, b, info, cur_cnt);
		if (cur_cnt[1] == (int)(info[1] / 2))
			break ;
		cnt--;
	}
	count += cur_cnt[0] + cur_cnt[1];
	count += check_partition(a, info[1] - cur_cnt[1], cur_cnt);
	return (count);
}

void	sort_using_one_A(t_Stack *a, t_Stack *b, int cnt, t_Pushswap *p)
{
	int		*cur_cnt;

	cur_cnt = (int *)malloc(sizeof(int) * 2);
	if (cur_cnt == NULL)
		return ;
	cur_cnt[0] = 0;
	cur_cnt[1] = 0;
	if (check_sorted(a, cnt))
		return ;
	if (cnt < 4)
	{
		sort_under_4_A(a, cnt, p);
		return ;
	}
	p->count += process_a_to_b_one(a, b, cnt, cur_cnt);
	sort_using_one_A(a, b, cnt - cur_cnt[1], p);
	sort_using_one_B(a, b, cur_cnt[1], p);
}
	/*
		cur_cnt[0] = 0; // cnt_ra
		cur_cnt[1] = 0; // cnt_pb
	*/