#include "stack_link_list.h"

element	peek_head(Stack *a)
{
	element	ret;

	if (IsEmpty(*a))
		return (NULL);
	ret = a->head->data;
	return (ret);
}

element	peek_tail(Stack *a)
{
	element	ret;

	if (IsEmpty(*a))
		return (NULL);
	ret = a->tail->data;
	return (ret);
}

element	peek_bottom(Stack *a)
{
	element	ret;

	if (IsEmpty(*a))
		return (NULL);
	ret = a->tail->data;
	return (ret);
}
