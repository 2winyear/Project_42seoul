#include <stdio.h>

void recursive(void){
    char *a;
    char *b;
    char *c;
    
    recursive();
}

int main(void){
    recursive();
    return (0);
}