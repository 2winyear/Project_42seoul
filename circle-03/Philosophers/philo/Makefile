NAME=philo
CFLAGS=-Wall -Wextra -Werror
SRCS_NAME=philosopher.c \
			util.c \
			init.c \
			free_check.c \
			time_to.c
INCFALGS=-I.
OBJS_NAME= $(SRCS_NAME:.c=.o)
OBJS_DIR= ./objs

OBJS= $(addprefix $(OBJS_DIR)/, $(OBJS_NAME))

all: $(NAME)

$(OBJS_DIR)/%.o: ./%.c
	@mkdir -p $(OBJS_DIR) 
	gcc $(CFLAGS) $(INCFALGS) -o $@ -c $<

$(NAME) : $(OBJS)
	gcc $(CFLAGS) $(INCFALGS) $(OBJS) -o $(NAME)

clean:
	rm -rf ./objs

fclean: clean
	rm -rf $(NAME)

re : fclean all