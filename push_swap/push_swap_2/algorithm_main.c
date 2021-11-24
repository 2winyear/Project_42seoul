#include "push_swap.h"
#include <stdlib.h>

void	b_to_a(Stack *a, Stack *b, int cnt, Pushswap *p);

void	a_to_b(Stack *a, Stack *b, int cnt, Pushswap *p)
{
	int	i;
	int	pivot_index_big;
	int	pivot_index_small;
	int	a_top;
	int	a_second;
	int	cnt_pb;
	int	cnt_ra;
	int	cnt_rb;

	cnt_pb = 0;
	cnt_ra = 0;
	cnt_rb = 0;
	if (a->head == NULL)
		return ;
	if (a == NULL || b == NULL)
		return ;
	if (cnt < 6)
	{
		if (cnt > 3)
			sort_under_6_over_3_A(a, b, cnt, p);
		else
			sort_under_4_A(a, b, cnt, p);
		return ;
	}
	pivot_index_big = get_high_pivot(*a, cnt);
	pivot_index_small = get_low_pivot(*a, cnt);
	while (!IsEmpty(*a) && cnt != 0)
	{
		a_top = atoi(a->head->data);
		if (a_top >= pivot_index_big)
		{
			ra(a, 0);
			cnt_ra++;
		}
		else
		{
			pb(a, b);
			cnt_pb++;
			if (a_top >= pivot_index_small)
			{
				rb(b, 0);
				cnt_rb++;
			}
		}
		cnt--;
	}
	p->count += cnt_ra + cnt_rb + cnt_pb;
	print_stack(a, b);
	if (cnt_ra - cnt_rb > 2 || cnt_ra - cnt_rb < -2)
	{
		printf("PIVOT_ERROR");
		return ;
	}
	if (cnt_ra < cnt_rb)
	{
		i = 0;
		while (i < cnt_ra)
		{
			rrr(a, b);
			i++;
		}	
		rrb(b, 0);
		p->count += cnt_rb;
	}
	else if (cnt_rb < cnt_ra)
	{
		i = 0;
		while (i < cnt_rb)
		{
			rrr(a, b);
			i++;
		}
		rra(a, 0);
		p->count += cnt_ra;
	}
	else
	{
		i = 0;
		while (i < cnt_ra)
		{
			rrr(a, b);
			i++;
		}
		p->count += cnt_ra;
	}
	print_stack(a, b);
	a_to_b(a, b, cnt_ra, p);
	b_to_a(a, b, cnt_rb, p);
	b_to_a(a, b, cnt_pb - cnt_rb, p);
}

void	b_to_a(Stack *a, Stack *b, int cnt, Pushswap *p)
{
	int	i;
	int	pivot_index_big;
	int	pivot_index_small;
	int	cnt_pa;
	int	cnt_ra;
	int	cnt_rb;
	int	b_top;

	cnt_pa = 0;
	cnt_ra = 0;
	cnt_rb = 0;
	if (a == NULL || b == NULL)
    	return ;
	if (cnt < 4)
	{
		sort_under_4_B(a, b, cnt, p);
		return ;
	}
	pivot_index_big = get_high_pivot(*b, cnt);
	pivot_index_small = get_low_pivot(*b, cnt);
	printf("At Stack B, pivot : (1)%d (2)%d (3)%d\n", pivot_index_big, pivot_index_small, cnt);
	print_stack(a, b);
	while(!IsEmpty(*b) && cnt != 0)
	{
		b_top = atoi(b->head->data);
		if (b_top < pivot_index_small)
		{
			rb(b, 0);
			cnt_rb++;
		}
		else
		{
			pa(a, b);
			cnt_pa++;
			if (b_top < pivot_index_big)
			{
				ra(a, 0);
				cnt_ra++;
			}
		}
		cnt--;
	}
	p->count += cnt_rb + cnt_ra + cnt_pa;
	printf("check stack B cnt_ra, cnt_rb, cnt_pa : %d %d %d\n", cnt_ra, cnt_rb, cnt_pa);
	print_stack(a, b);
	a_to_b(a, b, cnt_pa - cnt_ra, p);
	if (cnt_ra - cnt_rb > 2 || cnt_ra - cnt_rb < -2)
	{
		printf("PIVOT_ERROR");
		return ;
	}
	if (cnt_ra < cnt_rb)
	{
		i = 0;
		while (i < cnt_ra)
		{
			rrr(a, b);
			i++;
		}	
		rrb(b, 0);
		p->count += cnt_rb;
	}
	else if (cnt_rb < cnt_ra)
	{
		i = 0;
		while (i < cnt_rb)
		{
			rrr(a, b);
			i++;
		}	
		rra(a, 0);
		p->count += cnt_ra;
	}
	else
	{
		i = 0;
		while (i < cnt_ra)
		{
			rrr(a, b);
			i++;
		}
		p->count += cnt_ra;
	}
	a_to_b(a, b, cnt_ra, p);
	b_to_a(a, b, cnt_rb, p);
}

int main(int argc, char* argv[])
{
	Stack	*a;
	Stack	*b;
	Pushswap	*p;

    int tmp;
    int count;
    int sorted;
	sorted = TRUE;
	if (argc <= 1)
	{
		write(1, "Error", sizeof("Error"));
		return 0;
	}
	a = init();
	b = init();
	count = parcing_input(argc, argv, a);
	if (check_sorted(a) == TRUE)
		exit(0);
	p = push_swap_init();
	a_to_b(a, b, size(*a), p);
	printf("count : %d", p->count);
	print_stack(a, b);
	exit(0);
}