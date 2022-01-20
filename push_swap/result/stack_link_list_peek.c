#include "stack_link_list.h"

t_element	peek_head(t_Stack *a)
{
	t_element	ret;

	if (IsEmpty(*a))
		return (NULL);
	ret = a->head->data;
	return (ret);
}

t_element	peek_tail(t_Stack *a)
{
	t_element	ret;

	if (IsEmpty(*a))
		return (NULL);
	ret = a->tail->data;
	return (ret);
}

t_element	peek_bottom(t_Stack *a)
{
	t_element	ret;

	if (IsEmpty(*a))
		return (NULL);
	ret = a->tail->data;
	return (ret);
}
