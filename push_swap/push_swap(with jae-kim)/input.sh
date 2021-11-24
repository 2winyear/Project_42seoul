rm a.out
gcc *.c -fsanitize=address
./a.out 1 15 19 99 31 88 42 64 51 77 66 33 82 101 41 14 30