#include "link_list.h"

t_ListNode	*insert_first(t_ListNode *head, t_element value)
{
	t_ListNode	*p;

	p = (t_ListNode *) malloc(sizeof(t_ListNode));
	if (p == NULL)
		return (NULL);
	p->data = value;
	p->prev = NULL;
	p->next = NULL;
	if (head != NULL)
	{
		p->prev = head;
		head->next = p;
	}
	head = p;
	return (head);
}

t_ListNode	*delete_first(t_ListNode *head)
{
	t_ListNode	*removed;

	if (head == NULL)
		return (NULL);
	removed = head;
	if (head->prev == NULL)
	{
		free(removed);
		head = NULL;
	}
	else
	{
		head = removed->prev;
		head->next = NULL;
		free(removed);
	}
	return (head);
}

t_ListNode	*insert_last(t_ListNode *tail, t_element value)
{
	t_ListNode	*p;

	p = (t_ListNode *)malloc(sizeof(t_ListNode));
	p->data = value;
	p->prev = NULL;
	p->next = NULL;
	if (tail != NULL)
	{
		p->next = tail;
		tail->prev = p;
	}
	tail = p;
	return (tail);
}

t_ListNode	*delete_last(t_ListNode *tail)
{
	t_ListNode	*removed;

	if (tail == NULL)
	{
		free(tail);
		return (NULL);
	}
	removed = tail;
	if (tail->next == NULL)
	{
		free(removed);
		tail = NULL;
	}
	else
	{
		tail = removed->next;
		tail->prev = NULL;
		free(removed);
	}
	return (tail);
}
