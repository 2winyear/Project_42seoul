#include "push_swap.h"

    int parcing_input(int argc, char **argv, Stack *a){
        int input_count;
        char *input;

        // split 
        //printf("argc num : %d\n", argc);
        int i = 1;

        if (argc == 1){
            exit (0);
        }
        while (argv[i]){
            char **ptr;
            ptr = ft_split(argv[i], ' ');
            if (ft_strlen(ptr[0]) == ft_strlen(argv[i])){
                input = argv[i];
                if (check_valid_input(input, a) == TRUE){
                    push_tail(a,input);
                    input_count++;
                }else{
                    printf("Error");
                    exit (1);
                }
            }
            else {
                int j;
                j = 0;
                while (ptr[j]){
                    input = ptr[j];
                    if (check_valid_input(input, a) == TRUE){
                        push_tail(a,input);
                        input_count++;
                    }else{
                        printf("Error");
                        exit (1);
                    }
                    j++;
                }
            }
            i++;
        }
        return (input_count);

            // 문자열의 배열, 배열의 길이는 인자 값이면 1개가 아님 
            // printf("ptr check : %s %s\n", ptr[j], argv[i]);

            // printf("ptr check : %zu %zu\n", ft_strlen(ptr[j]), ft_strlen(argv[i]));
            // if(ptr[j] == argv[i])
            //     printf("true");
            
            // printf("argv : %s\n", argv[i]);
            // printf("len : %zu \n", ft_strlen(argv[i]));
            // i++;   
    }

    int check_valid_input(char *input, Stack *a){
        //중복인지
        //숫자가 아닌지
        //MAXINT값 이상의 값이 있을 경우, printf에서 쓴 atoi longlong  
        //파라미터 없을 경우 
        ListNode *ptr;
        int i;

        i = 0;
        ptr = a->head;
        // 중복 체킄 
        while (ptr){
            if (ptr->data == input)
                return FALSE;
            ptr = ptr->prev;
        }
        // 숫자가 아닌지
        while (input[i]){
            if (ft_isdigit(input[i] == 0))
                return (FALSE);
            i++;
        }
        // MAX_INT 이상인지
        if (atoi(input) > INT_MAX){
            return (FALSE);
        }
       return (TRUE); 
    }

    int check_sorted(Stack *a){
        ListNode *ptr;

        if (size(*a) < 2)
            return (TRUE);
        ptr = a->head;
        while (ptr->prev){
            if (atoi(ptr->data) > atoi(ptr->prev->data))
                return (FALSE);
            ptr = ptr->prev;
        }
        return (TRUE);
    }