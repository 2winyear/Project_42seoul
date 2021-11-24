TEST=test.out
NAME=cub3D
CFLAGS=-Wall -Wextra -Werror
MLXFLAGS=-lmlx -L./mlx -framework OpenGL -framework AppKit
MLXSCREENFLAGS =  -L. -lmlxscreen
SRCS_NAME=	cub3d.c\
			utility.c\
			init_option.c\
			init_cub.c\
			init_map.c\
			get_next_line_utils.c\
			get_next_line.c\
			save_bmp.c\
			wall.c\
			ft_mem.c\
			sprite.c\
			press.c\
			load.c\
			parse.c\
			free.c
INCFALGS=-I./mlx -I./includes
SRCS_DIR= ./srcs
SRCS=$(addprefix $(SRCS_DIR)/, $(SRCS_NAME))
OBJS_NAME= $(SRCS_NAME:.c=.o)
OBJS_DIR= ./objs
OBJS= $(addprefix $(OBJS_DIR)/, $(OBJS_NAME))

all: $(NAME)

.PHONY: test
test:
	gcc $(SRCS) $(MLXFLAGS) $(MLXSCREENFLAGS) $(INCFALGS) -o $(NAME)
	./$(NAME) ./cubs/map.cub

.PHONY: save
save:
	gcc $(SRCS) $(MLXFLAGS) $(MLXSCREENFLAGS) $(INCFALGS) -o $(NAME)
	./$(NAME) --save ./cubs/map.cub
	chmod 777 ./image.bmp

$(NAME) : $(OBJS)
	@$(MAKE) -C ./mlx all
	gcc $(CFLAGS) $(MLXFLAGS) $(MLXSCREENFLAGS) $(INCFALGS) $(SRCS) -o $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	@mkdir $(OBJS_DIR) 2> /dev/null || true
	gcc $(CFLAGS) $(INCFALGS) -o $@ -c $<

clean:
	@$(MAKE) -C ./mlx clean
	rm -rf ./objs image.bmp

fclean: clean
	@$(MAKE) -C ./mlx clean
	rm -rf ./objs $(NAME)

tclean:
	rm -rf objs $(TEST)

re : fclean all
