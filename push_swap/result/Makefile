CC = gcc
NAME=push_swap
SRCS = al_b_one_piv_sub.c\
		algorithm_a_to_b_one_pivot.c\
		algorithm_a_to_b.c\
		algorithm_b_to_a_one_pivot.c\
		algorithm_b_to_a.c\
		algorithm_main.c\
		algorithm_under_4_A.c\
		algorithm_under_4_B.c\
		check_sorted.c\
		check_valid_input.c\
		get_pivot.c\
		link_list.c\
		push_swap_1.c\
		push_swap_2.c\
		push_swap_3.c\
		stack_link_list_peek.c\
		stack_link_list_pushpop.c\
		stack_link_list.c\
		stack_print.c

C_FLAG = -Wall -Wextra -Werror
LIBFT = -Llibft -lft
$(NAME): $(LIBFT)
	${CC} ${C_FLAG} $(SRCS) -o ${NAME} ${LIBFT}
$(LIBFT):
	@$(MAKE) -C ./libft all

all: $(LIBFT) $(NAME)
clean:
		@$(MAKE) -C ./libft clean
		rm -f ${OBJS}
fclean: clean
		@$(MAKE) -C ./libft clean
		rm -f ${NAME}

re: fclean all
.PHONY: all clean fclean re
