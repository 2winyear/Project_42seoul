#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef char *element;
typedef struct ListNode { 
	element data;
	struct ListNode* prev;
  struct ListNode* next;
} ListNode;
ListNode* insert_first(ListNode* head, element value);
ListNode* insert_last(ListNode* tail, element value);
ListNode* delete_first(ListNode* head);
ListNode* delete_last(ListNode* tail);
void print_list(ListNode* head);