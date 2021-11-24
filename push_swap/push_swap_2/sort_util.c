#include "push_swap.h"

static int	check_value_in_array(int *s, int value, int cnt)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (-1);
	while (s[i] != -1 && i < cnt)
	{
		if (s[i] == value)
			return (1);
		i++;
	}
	return (0);
}

int	get_high_pivot(Stack s, int cnt)
{
	int	upper_cnt;
	int	max;
	int	top;
	int	size;
	int	i;
	int	*upper;
	int	num;
	ListNode	*ptr;

	if (cnt % 3 == 2)
		upper_cnt = (int)(cnt / 3) + 1;
	else
		upper_cnt = (int)(cnt / 3);
	if (!(upper = (int *)malloc(sizeof(int) * (upper_cnt))))
		exit(1);
	memset(upper, -1, upper_cnt * sizeof(int));
	i = 0;
	num = upper_cnt;
	while (num != 0)
	{
		max = -1;
		size = cnt;
		ptr = s.head;
		while (size != 0)
		{
			top = atoi(ptr->data);
			if (top > max)
			{
				if (check_value_in_array(upper, top, upper_cnt) == 0)
					max = top;
			}
			ptr = ptr->prev;
			size--;
		}
		upper[i] = max;
		i++;
		num--;
	}
	free (upper);
	return (max);
}

int	get_low_pivot(Stack s, int cnt)
{
	int	lower_cnt;
	int	min;
	int	top;
	int	size;
	int	i;
	int	*lower;
	int	num;
	ListNode	*ptr;

	if (cnt % 3 == 0 || cnt % 3 == 2)
		lower_cnt = (int)(cnt / 3) + 1;
	else if (cnt % 3 == 1)
		lower_cnt = (int)(cnt / 3) + 2;
	if (!(lower = (int *)malloc(sizeof(int) * (lower_cnt))))
		exit(1);
	memset(lower, -1, lower_cnt * sizeof(int));
	i = 0;
	num = lower_cnt;
	while (num != 0)
	{
		min = INT_MAX;
		size = cnt;
		ptr = s.head;
		while (size != 0)
		{
			top = atoi(ptr->data);
			if (top < min)
			{
				if (check_value_in_array(lower, top, lower_cnt) == 0)
					min = top;
			}
			ptr = ptr->prev;
			size--;
		}
		lower[i] = min;
		i++;
		num--;
	}
	free (lower);
	return (min);
}
