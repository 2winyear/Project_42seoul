#include "push_swap.h"

static int	get_index_max(t_Stack *a, int cnt, int index, int max)
{
	int				element;
	int				num;
	int				cur_max;
	t_ListNode		*ptr;

	while (index != 0)
	{
		num = cnt;
		ptr = a->head;
		cur_max = -1;
		while (num != 0)
		{
			element = ft_atoi(ptr->data);
			if (element > cur_max && element < max)
				cur_max = element;
			ptr = ptr->prev;
			num--;
		}
		max = cur_max;
		index--;
	}
	return (cur_max);
}

int	get_middle_pivot(t_Stack *a, int cnt)
{
	int			index;
	int			max;

	max = INT_MAX;
	if (cnt % 2 == 0)
		index = (int)(cnt / 2);
	else
		index = (int)(cnt / 2) + 1;
	return (get_index_max(a, cnt, index, max));
}

int	get_high_pivot(t_Stack *s, int cnt)
{
	int			upper_cnt;
	int			max;

	max = INT_MAX;
	if (cnt % 3 == 2)
		upper_cnt = (int)(cnt / 3) + 1;
	else
		upper_cnt = (int)(cnt / 3);
	return (get_index_max(s, cnt, upper_cnt, max));
}

int	get_low_pivot(t_Stack *s, int cnt)
{
	int			second_upper_cnt;
	int			max;

	max = INT_MAX;
	if (cnt % 3 == 2)
		second_upper_cnt = ((int)(cnt / 3)*2) + 2;
	else
		second_upper_cnt = ((int)(cnt / 3)*2);
	return (get_index_max(s, cnt, second_upper_cnt, max));
}

/*
static int check_value_in_array(int *s, int value, int cnt){
    int i;

    i = 0;
    if (s == NULL)
        return (-1);
    while(s[i] != -1 && i < cnt){
        if (s[i] == value){
            return 1;
        }
        i++;
    }
    return 0;
}
*/