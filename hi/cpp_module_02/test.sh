c++ *.cpp *.hpp -Wall -Wextra -Werror
rm -rf *.gch
./a.out | cat -e
rm -rf ./a.out