#include "push_swap.h"

void	process_main_b_to_a(t_Stack *a, t_Stack *b, int *info, int *ret)
{
	int		b_top;

	while (!IsEmpty(*b) && info[0] != 0)
	{
		b_top = ft_atoi(b->head->data);
		if (b_top < info[1])
		{
			rb(b, 0);
			ret[1]++;
		}
		else
		{
			pa(a, b);
			ret[2]++;
			if ((b_top < info[2]))
			{
				ra(a, 0);
				ret[0]++;
			}
		}
		info[0]--;
	}
}

int	*process_b_to_a(t_Stack *a, t_Stack *b, int cnt)
{
	int		info[3];
	int		*ret;

	ret = (int *)malloc(sizeof(int) * 3);
	if (ret == NULL)
		return (NULL);
	ret[0] = 0;
	ret[1] = 0;
	ret[2] = 0;
	info[2] = get_high_pivot(b, cnt);
	info[1] = get_low_pivot(b, cnt);
	info[0] = cnt;
	process_main_b_to_a(a, b, info, ret);
	return (ret);
}

void	b_to_a(t_Stack *a, t_Stack *b, int cnt, t_Pushswap *p)
{
	int	*cur_cnt;

	if (a == NULL || b == NULL)
		return ;
	if (check_reverse_sorted(b, cnt) == TRUE)
	{
		while (cnt != 0)
		{
			pa(a, b);
			p->count++;
			cnt--;
		}
		return ;
	}
	if (cnt < 6)
	{
		sort_using_one_B(a, b, cnt, p);
		return ;
	}
	cur_cnt = process_b_to_a(a, b, cnt);
	p->count += cur_cnt[0] + cur_cnt[1] + cur_cnt[2];
	a_to_b(a, b, cur_cnt[2] - cur_cnt[0], p);
	p->count += roll_back(a, b, cur_cnt[0], cur_cnt[1]);
	a_to_b(a, b, cur_cnt[0], p);
	b_to_a(a, b, cur_cnt[1], p);
}
