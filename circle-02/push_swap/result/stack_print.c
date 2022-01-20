#include "push_swap.h"

static void	print_part(t_ListNode *ptr1, t_ListNode *ptr2)
{
	int		len;

	len = 0;
	if (ptr1 == NULL)
		write(1, "_", sizeof("_"));
	else
		write(1, ptr1->data, ft_strlen(ptr1->data));
	write(1, " ", sizeof(" "));
	if (ptr2 == NULL)
		write(1, "_", sizeof("_"));
	else
		write(1, ptr2->data, ft_strlen(ptr2->data));
	write(1, "\n", sizeof("\n"));
}

void	print_stack(t_Stack *a, t_Stack *b)
{
	t_ListNode	*ptr1;
	t_ListNode	*ptr2;

	ptr1 = a->head;
	ptr2 = b->head;
	write(1, "\n", sizeof("\n"));
	while (ptr1 != NULL || ptr2 != NULL)
	{
		print_part(ptr1, ptr2);
		if (ptr1 != NULL)
			ptr1 = ptr1->prev;
		if (ptr2 != NULL)
			ptr2 = ptr2->prev;
	}
	write(1, "\n", sizeof("\n"));
}
