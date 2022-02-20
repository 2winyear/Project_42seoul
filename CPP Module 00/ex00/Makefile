CC = c++
CFLAGS = -Wall -Werror -Wextra

all : main

main : megaphone.o
	$(CC) $(CFLAGS) megaphone.o -o megaphone

megaphone.o : megaphone.cpp
	$(CC) $(CFLAGS) -c megaphone.cpp

.PHONEY: clean

re : fclean all

fclean: clean
	rm -rf megaphone

clean:
	rm -rf megaphone.o