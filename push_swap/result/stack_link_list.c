#include "stack_link_list.h"

t_Stack	*init(void)
{
	t_Stack	*a;

	a = (t_Stack *)malloc(sizeof(t_Stack));
	if (a == NULL)
		return (NULL);
	a->head = NULL;
	a->tail = NULL;
	a->count = 0;
	return (a);
}

void	delete_stack(t_Stack *a)
{
	if (IsEmpty(*a))
	{
		free(a);
		return ;
	}
	while (a->head != NULL)
		delete_first (a->head);
	free (a);
}

int	size(t_Stack a)
{
	return (a.count);
}

int	IsEmpty(t_Stack a)
{
	return (a.count == 0);
}

int	IsFull(t_Stack a)
{
	if (a.count >= MAX)
		return (1);
	return (0);
}
