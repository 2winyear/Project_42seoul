#include "link_list.h"
#include "stdio.h"

ListNode	*insert_first(ListNode *head, element value)
{
	ListNode	*p;

	p = (ListNode*)malloc(sizeof(ListNode));
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

ListNode	*delete_first(ListNode *head)
{
	ListNode	*removed;

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

ListNode	*insert_last(ListNode *tail, element value)
{
	ListNode	*p;

	p = (ListNode*)malloc(sizeof(ListNode));
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

ListNode	*delete_last(ListNode *tail)
{
	ListNode	*removed;

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