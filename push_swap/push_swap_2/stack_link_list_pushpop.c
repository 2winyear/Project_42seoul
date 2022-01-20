#include "stack_link_list.h"

void	push_head(Stack *a, element data)
{
	if (IsFull(*a))
	{
		write(1, "is Full", sizeof("is Full"));
		return ;
	}
	a->head = insert_first(a->head, data);
	if (a->tail == NULL)
		a->tail = a->head;
	a->count++;
}

void	push_tail(Stack *a, element data)
{
	if (IsFull(*a))
	{
		write(1, "is Full", sizeof("is Full"));
		return ;
	}
	a->tail = insert_last(a->tail, data);
	if (a->head == NULL)
		a->head = a->tail;
	a->count++;
}

element	pop_head(Stack *a)
{
	element	ret;

	if (IsEmpty(*a))
	{
		write(1, "is Empty", sizeof("is Empty"));
		return (NULL);
	}
	ret = a->head->data;
	if (size(*a) == 1)
		a->tail = NULL;
	a->head = delete_first(a->head);
	a->count--;
	return (ret);
}

element	pop_tail(Stack *a)
{
	element	ret;

	if (IsEmpty(*a))
	{
		write(1, "is Empty", sizeof("is Empty"));
		return (NULL);
	}
	ret = a->tail->data;
	if (size(*a) == 1)
		a->head = NULL;
	a->tail = delete_last(a->tail);
	a->count--;
	return (ret);
}

void	print_stack(Stack *a, Stack *b)
{
	int	len;
	ListNode	*ptr1;
	ListNode	*ptr2;

	ptr1 = a->head;
	ptr2 = b->head;
	write(1, "\n", sizeof("\n"));
	while (ptr1 != NULL || ptr2 != NULL)
	{
		len = 0;
		if (ptr1 == NULL)
			write(1, "_", sizeof("_"));
		else
			write(1, ptr1->data, strlen(ptr1->data));
		write(1, " ", sizeof(" "));
		if (ptr2 == NULL)
			write(1, "_", sizeof("_"));
		else
			write(1, ptr2->data, strlen(ptr2->data));
		write(1, "\n", sizeof("\n"));
		if (ptr1 != NULL)
			ptr1 = ptr1->prev;
		if (ptr2 != NULL)
			ptr2 = ptr2->prev;
	}
	write(1, "\n", sizeof("\n"));
}
