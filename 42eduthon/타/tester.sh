#!/bin/bash

num_exercise="4"

testdir="./srcs/"
userdir="../"
utilsdir="./utils/"

ckheader="check_forbidden_header.c"
ckleaks="check_leaks.c"
gnl="get_next_line.c"

timeout=10

filename[0]="eleven_number_checker.c"
filename[1]="phone_number_checker.c"
filename[2]="simple_password_validator.c"
filename[3]="push_swap_instruction_validator.c"
filename[4]="snake_to_camel.c"

RED="\x1b[38;5;160m"
BLUE="\x1b[38;5;38m"
GREEN="\x1b[38;5;76m"
NOCOLOR="\x1b[0;0m"

fail=0

gcc -Wall -Wextra -Werror "$utilsdir""$gnl" "$utilsdir""$ckheader" -o "header_checker"

for num in $(seq 0 $num_exercise)
do
	testoutput="$testdir""ex0$num/""test$num.output"
	usersrc="$userdir""ex0$num/""${filename[$num]}"
	main="$testdir""ex0$num/""main.c"

	echo
	echo -e "${BLUE}Check Forbidden Header${NOCOLOR}"

	./header_checker "$usersrc"
	if [ $? != 0 ]
	then
		echo -e "${RED}Forbidden Header in ex0$num${NOCOLOR}"
		fail=1
		break
	fi

	echo
	echo -e "${BLUE}Check Norminette${NOCOLOR}"

	norminette "$usersrc"
	if [ $? != 0 ]
	then
		echo -e "${RED}Norm Error in ex0$num${NOCOLOR}"
		fail=1
		break
	fi

	echo
	echo -e "${BLUE}Compile and Check Error${NOCOLOR}"

	gcc -Wall -Wextra -Werror "$main" "$usersrc" "$utilsdir""$ckleaks" -o "user0$num.out"
	if [ $(echo $?) -gt 0 ]
	then
		echo -e "${RED}compile error in ex0$num${NOCOLOR}"
		fail=1
		break
	fi

	./user0$num.out > user.output 2> user.error
	ret=$(echo $?)

	echo
	echo -e "${BLUE}Check Unexpected Exit${NOCOLOR}"

	if [ $ret != 0 ]
	then
		echo -e "${RED}Fail in ex0$num${NOCOLOR}"
		echo -e "${RED}exit status: $ret${NOCOLOR}"
		fail=1
		break
	fi

	diff user.output $testoutput > diff.output

	echo
	echo -e "${BLUE}Compare Result${NOCOLOR}"

	if [ $(cat diff.output | wc -l) -gt 0 ]
	then
		echo -e "${RED}Fail in ex0$num${NOCOLOR}"
		cat diff.output
		fail=1
		break
	else
		echo -e "${GREEN}Success ex0$num${NOCOLOR}"
	fi
done

rm -rf header_checker

rm -rf user*.out

rm -rf user*.output
rm -rf diff.output

rm -rf user*.error
rm -rf diff.error

if [ $fail == 0 ]
then
	echo -e "${GREEN}All Success!${NOCOLOR}"
fi
exit $fail
