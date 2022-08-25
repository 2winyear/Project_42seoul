# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alee <alee@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/24 07:58:27 by mgo               #+#    #+#              #
#    Updated: 2022/08/24 10:01:58 by alee             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC			=	gcc
#CFLAGS		=	-Wall -Wextra -Werror
#CFLAGS		+=	-fsanitize=address -g
RM			=	rm -rf

DIR_SERV		=	./ft_ttt_server/
SRC_LIST_SERV	=	main.c \
					client_session.c \
					server.c
SRC_SERV		=	$(addprefix $(DIR_SERV), $(SRC_LIST_SERV))
OBJ_SERV		=	$(SRC_SERV:.c=.o)
#NAME_SERV		=	$(addprefix $(DIR_SERV), sv)
NAME_SERV		=	sv

DIR_CLNT		=	./ft_single_client/
SRC_LIST_CLNT	=	tictactoe.c
SRC_CLNT		=	$(addprefix $(DIR_CLNT), $(SRC_LIST_CLNT))
OBJ_CLNT		=	$(SRC_CLNT:.c=.o)
NAME_CLNT		=	$(addprefix $(DIR_CLNT), cl)
NAME_CLNT		=	cl

#DIR_CLNT		=	./ft_ttt_client/
#SRC_LIST_CLNT	=	main.c \
					client.c \
					tictactoe.c
#SRC_CLNT		=	$(addprefix $(DIR_CLNT), $(SRC_LIST_CLNT))
#OBJ_CLNT		=	$(SRC_CLNT:.c=.o)
#NAME_CLNT		=	$(addprefix $(DIR_CLNT), cl)
#NAME_CLNT		=	cl

%.o	:	%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME_SERV)	:	$(OBJ_SERV)
	$(CC) $(CFLAGS) $(OBJ_SERV) -o $(NAME_SERV)

$(NAME_CLNT)	:	$(OBJ_CLNT)
	$(CC) $(CFLAGS) $(OBJ_CLNT) -o $(NAME_CLNT)

all		:	$(NAME_CLNT) $(NAME_SERV)

c		:	$(NAME_CLNT)

s		:	$(NAME_SERV)

test	:
	$(CC) $(CFLAGS) ./tester/tester.c ./tester/get_next_line.c ./tester/get_next_line_utils.c -o tester_ttt

clean	:
	$(RM) $(OBJ_SERV)
	$(RM) $(OBJ_CLNT)

fclean	: clean
	$(RM) $(NAME_SERV)
	$(RM) $(NAME_CLNT)

re	:	fclean all

.PHONY	:	all clean fclean re c s
