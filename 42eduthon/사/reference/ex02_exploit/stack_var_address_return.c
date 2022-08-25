#include <stdio.h>

int *stack_function(void){
    int a = 10;
    int *b;

    b = &a;
    return b;
}

int *stack_function2(void){
	int a = 30;
    int b = 20;
	int c = 40;
    int *d;

    d = &a;
    return d;
}

int main(void) {
    int *a;

    a = stack_function();
    printf("stack_function called: %d\n", *a);
    stack_function2();
    printf("stack_function2 called: %d\n", *a);
    return (0);
}