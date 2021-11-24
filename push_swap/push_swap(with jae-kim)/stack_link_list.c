#include "stack_link_list.h"

#include <stdio.h>

Stack *init(void){
	Stack *a;

	if (!(a = (Stack *)malloc(sizeof(Stack))))
    return NULL;
  a->head = NULL;
  a->tail = a->head;
	a->count = 0;
	return a;
}

void delete_stack(Stack *a){
  ListNode *tmp;
  
  if(IsEmpty(*a)){
    free(a);
    return ;
  }
  while (a->head != NULL){
    delete_first(a->head);
  }
  free(a);
}

int size(Stack a){
    return a.count;
}

int IsEmpty(Stack a){
	return a.count == 0;
}

int IsFull(Stack a) {
    if (a.count >= MAX)
        return 1;
    return 0;
}

void push_head(Stack *a, element data){
	if (IsFull(*a))
	{
    write(1, "is Full", sizeof("is Full"));
		return;
	}
  a->head = insert_first(a->head, data);
  if (a->tail == NULL)
    a->tail = a->head;
	a->count++;
}

void push_tail(Stack *a, element data){
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

element pop_head(Stack *a){
  element ret;

  if (IsEmpty(*a))
	{
    write(1, "test", sizeof("test"));
		return NULL;
	}
  ret = a->head->data;
  a->head = delete_first(a->head);
  a->count--;
  return ret;
}

element pop_tail(Stack *a){
  element ret;

  if (IsEmpty(*a))
	{
    write(1, "test", sizeof("test"));
		return NULL;
	}
  ret = a->tail->data;
  a->tail = delete_last(a->tail);
  a->count--;
  return ret;
}

element	peek_head(Stack *a){
  element ret;
    
  if (IsEmpty(*a))
    return NULL;
  ret = a->head->data;
  return ret;     
}

element	peek_tail(Stack *a){
  element ret;
    
  if (IsEmpty(*a))
    return NULL;
  ret = a->tail->data;
  return ret;     
}

element peek_bottom(Stack *a){
  element ret;

  if (IsEmpty(*a))
    return NULL;
  ret = a->tail->data;
  return ret;
}

#include <string.h>
void print_stack(Stack *a, Stack *b){

    ListNode *ptr1, *ptr2;

    ptr1 = a->head;
    ptr2 = b->head; 
    while(ptr1 != NULL || ptr2 != NULL){
        
        int len = 0;
        if (ptr1 == NULL)
        {
          write(1, "_", sizeof("_"));
        }
        else
        {
          write(1, ptr1->data, strlen(ptr1->data));
          
        }
        write(1, " ", sizeof(" "));
        if (ptr2 == NULL)
        {
          write(1, "_", sizeof("_"));
        }
        else
        {
          write(1, ptr2->data, strlen(ptr2->data));
        }
        write(1, "\n", sizeof("\n"));

        
        if (ptr1 != NULL)
          ptr1 = ptr1->prev;
        if (ptr2 != NULL)
          ptr2 = ptr2->prev;
        
    }
}
