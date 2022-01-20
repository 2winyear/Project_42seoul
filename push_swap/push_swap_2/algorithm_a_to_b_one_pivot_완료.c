#include "push_swap.h"

int	process_main_a_to_b_one_pivot(Stack *a, Stack *b, int *info, int *ret)
{
	ListNode	*ptr;
	int			count;

	count = 0;
	ptr = a->head;
	if (ft_atoi(ptr->data) < info[0])
	{
		pb(a, b);
		ret[1]++;
	}
	else
	{
		if ((ret[1] == (info[1] - (int)(info[1]/2) - 1)) && (ft_atoi(ptr->prev->data) < info[0]))
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
	}
	return (count);
}
int		check_partition(Stack *a, int cnt, int *cur_cnt)
{
    int part;
    int ret;
    int i;

    i = 0;
    part = TRUE;
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
void process_a_to_b_one(Stack *a, Stack *b, int cnt, int *cur_cnt, Pushswap *p)
{
    int info[2];
    int i;

    info[0] = get_middle_pivot(a, cnt);
    info[1] = cnt;
    i = 0;
    while (cnt != 0)
    {
        p->count += process_main_a_to_b_one_pivot(a, b, info, cur_cnt);
		if (cur_cnt[1] == (int)(cnt/2))
			break;
        cnt--;
    }
    p->count += cur_cnt[0] + cur_cnt[1];
    p->count += check_partition(a, cnt, cur_cnt);
}

void sort_using_one_A(Stack *a, Stack *b, int cnt, Pushswap *p){
    int *cur_cnt;

    cur_cnt[0] = 0; // cnt_ra
    cur_cnt[1] = 0; // cnt_pb
    if (check_sorted(a, cnt))
        return ;
	if (cnt < 4)
	{
		sort_under_4_A(a, b, cnt, p);
		return ;
	}
    process_a_to_b_one(a, b, cnt , cur_cnt, p);
    sort_using_one_A(a, b, cnt - cur_cnt[1], p);
    b_to_a(a, b, cur_cnt[1], p);
}

    /*
		cur_cnt[0] = 0; // cnt_ra
    	cur_cnt[1] = 0; // cnt_pb
        ptr = a->head;
        if (ft_atoi(ptr->data) < pivot) // 지금 n, n+1 개씩 먹음 
        {
            pb(a, b);
            cnt_pb++;//info[1]
            p->count++;
        }
        else
        {
            if ((cnt_pb == (cnt - (int)(cnt/2) - 1)) && (ft_atoi(ptr->prev->data) < pivot))
            {
                sa(a, 0);
                pb(a, b);
                cnt_pb++;
                p->count += 2;
            } 
            else
            {
                ra(a, 0);
                cnt_ra++;//info[0]
                p->count++;
            }
        }
        */