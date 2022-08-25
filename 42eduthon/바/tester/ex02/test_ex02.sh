#!/bin/bash

## ft_exception dash ex02 tester

# # 현재 디렉토리로 복사
echo 'Copy files:'
cp ../../ex02/catch_me.c ./ex02.c

# 컴파일 검사
echo 'Compile test #1'
if ! cc -Wall -Wextra -Werror ex02.c test_ex02.c test_ex02_case00.c -o test_generated
then
    echo 'Does not compiled. KO :('
    exit 1
fi

echo 'Compile test #2'
if ! cc -Wall -Wextra -Werror ex02.c test_ex02.c test_ex02_case01.c -o test_generated2
then
    echo 'Does not compiled. KO :('
    exit 1
fi

# 프로그램 검사
# 6: Abord
# 8: Floating point error
# 10: Bus error
# 11: Segmentation fault
# 13: Broken pipe
ARR='6 8 10 11 13'
idx=1
for i in $ARR
do
    ./test_generated $i
    if [ ! $? ]
    then
        echo "Program test $idx failed. KO :("
        exit 1
    fi
    ./test_generated2 $i
    if [ ! $? ]
    then
        echo "Program test $idx failed. KO :("
        exit 1
    fi
    echo "Program test $((idx++)). OK :)"
done
# 30: User1
# 31: User2
BAD_ARR='30 31'
for i in $BAD_ARR
do
    ./test_generated $i
    if [ ! $? ]
    then
        echo "Program test $idx failed. KO :("
        exit 1
    fi
    ./test_generated2 $i
    if [ ! $? ]
    then
        echo "Program test $idx failed. KO :("
        exit 1
    fi
    echo "Program test $((idx++)). OK :)"
done

echo "Exercise success!"
