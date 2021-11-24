#include "push_swap.h"

int	input_case_correspond(char **argv, t_Stack *a, int i)
{
	int			input_count;
	char		*input;

	input_count = 0;
	input = argv[i];
	if (check_valid_input(input, a) == TRUE)
	{
		push_tail(a, input);
		input_count++;
	}
	else
	{
		write(1, "Error", 5);
		exit (1);
	}
	return (input_count);
}

int	input_case_split(t_Stack *a, char **ptr)
{
	int			j;
	char		*input;
	int			input_count;

	j = 0;
	input_count = 0;
	while (ptr[j])
	{
		input = ptr[j];
		if (check_valid_input(input, a) == TRUE)
		{
			push_tail(a, input);
			input_count++;
		}
		else
		{
			write(1, "Error", 5);
			exit (1);
		}
		j++;
	}
	return (input_count);
}

int	parcing_input(char **argv, t_Stack *a)
{
	int			i;
	int			count;
	char		**ptr;

	i = 1;
	count = 0;
	while (argv[i])
	{
		ptr = ft_split(argv[i], ' ');
		if (ft_strlen(ptr[0]) == ft_strlen(argv[i]))
			count += input_case_correspond(argv, a, i);
		else
			count += input_case_split(a, ptr);
		i++;
	}
	return (count);
}

int	check_valid_input(char *input, t_Stack *a)
{
	t_ListNode	*ptr;
	int			i;

	i = 0;
	ptr = a->head;
	while (ptr)
	{
		if (ft_atoi(ptr->data) == ft_atoi(input))
			return (FALSE);
		ptr = ptr->prev;
	}
	while (input[i])
	{
		if (ft_isdigit(input[i]) == 0)
			return (FALSE);
		i++;
	}
	if (ft_atoi(input) > INT_MAX || (ft_strlen(input) > 11))
		return (FALSE);
	return (TRUE);
}
