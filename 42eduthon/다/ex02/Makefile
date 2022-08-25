NAME = main
LIB = lib
TEST = test_files

all:
	gcc -Wall -Wextra -Werror main.c -L$(LIB) -lft -o $(NAME)
	./main $(TEST)/first_menu $(TEST)/second_menu $(TEST)/today_menu
clean:
	rm -rf $(NAME)
	rm -rf out_file
