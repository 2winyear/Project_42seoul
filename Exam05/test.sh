c++ *.cpp *.hpp -Wall -Werror -Wextra
rm -rf *.gch
./a.out | cat -e
rm -rf ./a.out