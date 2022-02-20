CC = c++
CFLAGS = -Wall -Werror -Wextra

main : megaphone.o
	$(CC) $(CFLAGS) megaphone.o -o megaphone

megaphone.o : megaphone.cpp
	$(CC) $(CFLAGS) -c megaphone.cpp

.PHONEY: clean

clean:
	rm -rf megaphone.o megaphone