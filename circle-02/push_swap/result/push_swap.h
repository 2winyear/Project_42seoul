#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# define TRUE 1
# define FALSE 0
# define INT_MAX 2147483647
# include "stack_link_list.h"
# include "libft/libft.h"

typedef struct s_Pushswap {
	int		count;
}				t_Pushswap;

t_Pushswap		*push_swap_init(void);
int				sa(t_Stack *a, int ss);
int				sb(t_Stack *b, int ss);
int				ss(t_Stack *a, t_Stack *b);
int				pa(t_Stack *a, t_Stack *b);
int				pb(t_Stack *a, t_Stack *b);
int				ra(t_Stack *a, int rr);
int				rb(t_Stack *b, int rr);
int				rr(t_Stack *a, t_Stack *b);
int				rra(t_Stack *a, int rrr);
int				rrb(t_Stack *b, int rrr);
int				rrr(t_Stack *a, t_Stack *b);

void			sort_under_4_A(t_Stack *a, int cnt, t_Pushswap *p);
void			sort_under_4_B(t_Stack *a, t_Stack *b, int cnt, t_Pushswap *p);
void			sort_using_one_A(t_Stack *a, t_Stack *b, int cnt, \
t_Pushswap *p);
void			sort_using_one_B(t_Stack *a, t_Stack *b, int cnt, \
t_Pushswap *p);
void			a_to_b(t_Stack *a, t_Stack *b, int cnt, t_Pushswap *p);
void			b_to_a(t_Stack *a, t_Stack *b, int cnt, t_Pushswap *p);

int				process_at_b_stack(t_Stack *a, t_Stack *b, int *info, int *ret);
int				process_main_b_to_a_one_pivot(t_Stack *a, \
		t_Stack *b, int *info, int *ret);

int				parcing_input(char **argv, t_Stack *a);
int				check_valid_input(char *input, t_Stack *a);
int				check_sorted(t_Stack *a, int cnt);
int				check_reverse_sorted(t_Stack *b, int cnt);

int				roll_back(t_Stack *a, t_Stack *b, int cnt_ra, int cnt_rb);
int				get_low_pivot(t_Stack	*s, int	cnt);
int				get_high_pivot(t_Stack	*s, int	cnt);
int				get_middle_pivot(t_Stack *a, int cnt);

#endif
