#include "push_swap.h"

void	process_main_a_to_b(t_Stack *a, t_Stack *b, int *info, int *ret)
{
	int		a_top;

	while (!IsEmpty(*a) && info[0] != 0)
	{
		a_top = ft_atoi(a->head->data);
		if (a_top >= info[2])
		{
			ra(a, 0);
			ret[0]++;
		}
		else
		{
			pb(a, b);
			ret[2]++;
			if ((a_top >= info[1]))
			{
				rb(b, 0);
				ret[1]++;
			}
		}
		info[0]--;
	}
}

int	*process_a_to_b(t_Stack *a, t_Stack *b, int cnt)
{
	int		info[3];
	int		*ret;

	ret = (int *)malloc(sizeof(int) * 3);
	ret[0] = 0;
	ret[1] = 0;
	ret[2] = 0;
	info[2] = get_high_pivot(a, cnt);
	info[1] = get_low_pivot(a, cnt);
	info[0] = cnt;
	process_main_a_to_b(a, b, info, ret);
	return (ret);
}

void	a_to_b(t_Stack *a, t_Stack *b, int cnt, t_Pushswap *p)
{
	int		*cur_cnt;

	if (a == NULL || b == NULL || check_sorted(a, cnt) == TRUE)
		return ;
	if (cnt < 100)
	{
		sort_using_one_A(a, b, cnt, p);
		return ;
	}
	cur_cnt = process_a_to_b(a, b, cnt);
	p->count += cur_cnt[0] + cur_cnt[1] + cur_cnt[2];
	p->count += roll_back(a, b, cur_cnt[0], cur_cnt[1]);
	a_to_b(a, b, cur_cnt[0], p);
	b_to_a(a, b, cur_cnt[1], p);
	b_to_a(a, b, cur_cnt[2] - cur_cnt[1], p);
	free(cur_cnt);
}

/*

 //ret[0] = ra, ret[1] = rb, ret[2] = pb
int get_max(int cnt, int code){
  int max_ra;
  int max_pb;
  int max_rb;
  int n;

  n = (int)(cnt/3);
  if (cnt % 3 == 2){
    max_ra = n + 1;
    max_rb = n + 1;
    max_pb = 2 * n + 1;
  }
  else if (cnt % 3 == 1){
    max_ra = n;
    max_rb = n;
    max_pb = 2 * n + 1;
  }
  else {
    max_ra = n;
    max_rb = n;
    max_pb = 2 * n;
  }

  if (code == 1)
    return (max_ra);
  if (code == 2)
    return (max_rb);
  if (code == 3)
    return (max_pb);

  return (0);
}

int check_already_divided(int cnt, int cur_cnt, int code){
  int max_ra;
  int max_pb;
  int max_rb;

  max_ra = get_max(cnt, 1);
  max_rb = get_max(cnt, 2);
  max_pb = get_max(cnt, 3);

  if ((code == 1) && (cur_cnt == max_pb))
    return (TRUE);
  if ((code == 2) && (cur_cnt == max_pb - max_rb))
    return (TRUE);

  return (FALSE);

}
  pivot_index_big = get_high_pivot(*a, cnt);
  pivot_index_small = get_low_pivot(*a, cnt);
  while(!IsEmpty(*a) && cnt != 0) // ra, rb 최적화 포함
  {
    a_top = ft_atoi(a->head->data);
    if (a_top >= pivot_index_big)
	{
      ra(a, 0);
      cnt_ra++;
    }
    else
	{
      pb(a, b);
      cnt_pb++;
      if ((a_top >= pivot_index_small))
      {
		rb(b, 0);
        cnt_rb++;
      }
	}
    cnt--;
  }
  */