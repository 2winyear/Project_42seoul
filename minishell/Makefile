NAME = minishell
CFLAGS = -g3 -Wall -Wextra -Werror -I include
READCFLAGS1 = -L $(HOME)/.brew/opt/readline/lib -lreadline
READCFLAGS2 = -I~/.brew/opt/readline/include
SRCS_NAME = minishell.c \
			ft_cd.c \
			ft_echo.c \
			ft_exit.c \
			ft_export.c \
			ft_unset.c \
			delete_deque.c \
			edit_deque.c \
			read.c \
			ft_split.c \
			command_util1.c \
			command_util2.c \
			parsing_main.c \
			act_process.c \
			redirection.c \
			env_util.c \
			init.c \
			util.c \
			util1.c \
			util2.c \
			util3.c

SRCS_DIR = ./src

OBJS_NAME = $(SRCS_NAME:.c=.o)
OBJS_DIR = ./objs
SRCS = $(addprefix $(SRCS_DIR)/, $(SRCS_NAME))
OBJS = $(addprefix $(OBJS_DIR)/, $(OBJS_NAME))

all: $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir -p $(OBJS_DIR)
	gcc $(CFLAGS) $(READCFLAGS2) -c $< -o $@

$(NAME) : $(OBJS)
	gcc $(CFLAGS) $(OBJS) -o $@ $(READCFLAGS2) $(READCFLAGS1)

clean:
	rm -rf ./objs

fclean: clean
	rm -rf $(NAME)

re : fclean all
