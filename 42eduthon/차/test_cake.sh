make re

#OK
echo "\033[0;92mtester: \nOK \n\033[0m your algorithm:"
./vpdlwldkfrhflwma 1 2 3  | ./corrector 1 2 3

#Error
echo "\033[0;92mtester: \nError \n\033[0m your algorithm:"
./vpdlwldkfrhflwma -1 2 3  | ./corrector -1 2 3

#Error
echo "\033[0;92mtester: \nError \n\033[0m your algorithm:"
./vpdlwldkfrhflwma 0 2 3  | ./corrector 0 2 3

#OK
echo "\033[0;92mtester: \nOK \n\033[0m your algorithm:"
./vpdlwldkfrhflwma +1 2 3  | ./corrector +1 2 3

#Error
echo "\033[0;92mtester: \nError \n\033[0m your algorithm:"
./vpdlwldkfrhflwma ++1 2 3  | ./corrector ++1 2 3

#KO
echo "\033[0;92mtester: \nKO \n\033[0m your algorithm:"
./vpdlwldkfrhflwma 1 2 3  | ./corrector 1 2 3 3

#KO
echo "\033[0;92mtester: \nKO \n\033[0m your algorithm:"
./vpdlwldkfrhflwma 1 2 3  | ./corrector 1 2

#OK
echo "\033[0;92mtester: \nOK \n\033[0m your algorithm:"
./vpdlwldkfrhflwma 1 2 3 4 5 6 7 1 2 3 4 5 6 7  | ./corrector 1 2 3 4 5 6 7 1 2 3 4 5 6 7

#OK
echo "\033[0;92mtester: \nOK \n\033[0m your algorithm:"
ARG=`jot -r 500 1 200 | tr '\n' ' '` ; ./vpdlwldkfrhflwma $ARG | ./corrector $ARG

echo "\033[0;92mtester: \nOK \n\033[0m your algorithm: (EOF)"
#OK (ctrl-d)
./vpdlwldkfrhflwma 
./corrector 
