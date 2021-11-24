#include "stack_link_list.h"

Stack	*init(void)
{
	Stack	*a;

	if (!(a = (Stack *)malloc(sizeof(Stack))))
		return (NULL);
	a->head = NULL;
	a->tail = NULL;
	a->count = 0;
	return (a);
}

void	delete_stack(Stack *a)
{
	ListNode	*tmp;

	if (IsEmpty(*a))
	{
		free(a);
		return ;
	}
	while (a->head != NULL)
		delete_first (a->head);
	free (a);
}

int	size(Stack a)
{
	return (a.count);
}

int	IsEmpty(Stack a)
{
	return (a.count == 0);
}

int	IsFull(Stack a)
{
	if (a.count >= MAX)
		return (1);
	return (0);
}
