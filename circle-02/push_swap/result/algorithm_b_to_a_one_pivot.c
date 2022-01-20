#include "push_swap.h"

static int	check_partition(t_Stack *b, int cnt, int *cur_cnt)
{
	int		part;
	int		ret;
	int		i;

	i = 0;
	ret = 0;
	part = TRUE;
	if (size(*b) == cnt)
		part = FALSE;
	if (part == TRUE)
	{
		while (i < cur_cnt[0])
		{
			rrb(b, 0);
			ret++;
			i++;
		}
	}
	return (ret);
}

int	process_b_to_a_one(t_Stack *a, t_Stack *b, int cnt, int *cur_cnt)
{
	int		info[2];
	int		count;

	count = 0;
	info[0] = get_middle_pivot(b, cnt);
	info[1] = cnt;
	while (cnt != 0)
	{
		count += process_main_b_to_a_one_pivot(a, b, info, cur_cnt);
		if (cur_cnt[1] == (int)(info[1] / 2))
			break ;
		cnt--;
	}
	count += cur_cnt[0] + cur_cnt[1];
	count += check_partition(b, info[1] - cur_cnt[1], cur_cnt);
	return (count);
}

static int	exception_check(t_Stack *a, t_Stack *b, int cnt, t_Pushswap *p)
{
	int		num;

	num = cnt;
	if (check_reverse_sorted(b, cnt) == TRUE)
	{
		while (num != 0)
		{
			pa(a, b);
			p->count++;
			num--;
		}
		return (TRUE);
	}
	if (cnt < 4)
	{
		sort_under_4_B(a, b, cnt, p);
		return (TRUE);
	}
	return (FALSE);
}

void	sort_using_one_B(t_Stack *a, t_Stack *b, int cnt, t_Pushswap *p)
{
	int		*cur_cnt;

	cur_cnt = (int *)malloc(sizeof(int) * 2);
	if (cur_cnt == NULL)
		return ;
	cur_cnt[0] = 0;
	cur_cnt[1] = 0;
	if (exception_check(a, b, cnt, p))
		return ;
	p->count += process_b_to_a_one(a, b, cnt, cur_cnt);
	sort_using_one_A(a, b, cur_cnt[1], p);
	sort_using_one_B(a, b, cnt - cur_cnt[1], p);
	free(cur_cnt);
}
	//cur_cnt[0] = 0; // cnt_rb
	//cur_cnt[1] = 0; // cnt_pa
	// rb : ret[0]
	// pa : ret[1]
	// info[0] : pivot
	// info[1] : cnt
