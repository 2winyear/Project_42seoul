#ifndef LINK_LIST_H
# define LINK_LIST_H

# include <unistd.h>
# include <stdlib.h>
# include "libft/libft.h"

typedef char	*t_element;
typedef struct s_ListNode
{
	t_element			data;
	struct s_ListNode	*prev;
	struct s_ListNode	*next;
}				t_ListNode;
t_ListNode	*insert_first(t_ListNode *head, t_element value);
t_ListNode	*insert_last(t_ListNode	*tail, t_element value);
t_ListNode	*delete_first(t_ListNode *head);
t_ListNode	*delete_last(t_ListNode	*tail);
void		print_list(t_ListNode *head);
#endif
