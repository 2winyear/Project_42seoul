CC = g++
CFLAGS = -Wall -Werror -Wextra

main : main.o phonebook.o
	$(CC) $(CFLAGS) main.o phonebook.o -o phonebook

main.o : main.cpp
	$(CC) $(CFLAGS) -c main.cpp

phonebook.o : phonebook.cpp
	$(CC) $(CFLAGS) -c phonebook.cpp

.PHONEY: clean

clean:
	rm -rf phonebook.o main.o phonebook