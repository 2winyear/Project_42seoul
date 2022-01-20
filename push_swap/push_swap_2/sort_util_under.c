#include "push_swap.h"

void	sort_under_6_over_3_A(Stack *a, Stack *b, int cnt, Pushswap *p)
{
	int	min;
	int	head;
	int	post_head;
	int	tail;
	int	code;
	int	num;

	num = cnt;
	while (num > 3)
	{
		print_stack(a, b);
		min = INT_MAX;
		head = atoi(a->head->data);
		post_head = atoi(a->head->prev->data);
		tail = atoi(a->tail->data);
		if (head > post_head)
		{
			min = post_head;
			code = 2;
		}
		else
		{
			min = head;
			code = 1;
		}
		if (min > tail)
		{
			min = tail;
			code = 3;
		}
		if (code == 1)
		{
			pb(a, b);
			p->count++;
		}
		else if (code == 2)
		{
			sa(a, 0);
			pb(a, b);
			p->count += 2;
		}
		else
		{
			rra(a, 0);
			pb(a, b);
			p->count += 2;
		}
		if (num == 5 && code == 3)
		{
			rra(a, 0);
			p->count++;
		}
		else if (num == 5)
		{
			ra(a, 0);
			p->count++;
		}
		num--;
	}
	sort_under_4_A(a, b, num, p);
	sort_under_4_B(a, b, 2, p);
}

void	sort_under_4_A(Stack *a, Stack *b, int cnt, Pushswap *p)
{
	int	a_top;
	int	a_second;
	int	min;
	int	num;
	int	tmp_cnt;
	int	rotate_num;
	ListNode	*ptr;

	if (cnt == 0)
		return ;
	num = cnt;
	ptr = a->head;
	if (cnt >= 2)
	{
		if (atoi(ptr->prev->data) < atoi(ptr->data))
		{
			sa(a, 0);
			p->count++;
		}
		ptr = a->head->prev;
		if (cnt == 3)
		{
			if (atoi(ptr->prev->data) < atoi(ptr->data))
			{
				rra(a, 0);
				p->count++;
				ptr = a->head;
				if (atoi(ptr->data) > atoi(ptr->prev->data))
				{
					sa(a, 0);
					p->count++;
				}
			}
		}
	}
}

void	sort_under_4_B(Stack *a, Stack *b, int cnt, Pushswap *p)
{
	int	b_top;
	int	max;
	int	num;
	int	tmp_cnt;
	int	rotate_num;
	ListNode	*ptr;

	num = cnt;
	if (cnt == 0)
		return ;
	ptr = b->head;
	if (cnt >= 2)
	{
		if (atoi(ptr->prev->data) > atoi(ptr->data))
		{
			sb(b, 0);
			p->count++;
		}
		if (cnt == 3)
		{
			ptr = b->tail;
			if (atoi(ptr->data) > atoi(b->head->data))
			{
				rrb(b, 0);
				pa(a, b);
				p->count += 2;
			}
			else
			{
				pa(a, b);
				p->count++;
			}
		}
		ptr = b->head;
		if (ptr->data < ptr->prev->data)
		{
			sb(b, 0);
			p->count++;
		}
		pa(a, b);
		p->count++;
	}
	pa(a, b);
	p->count++;
}
