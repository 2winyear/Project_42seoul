#include <stdlib.h>
#include <stdio.h>

void free_strs(char **strs){
    while (*strs){
        free(*strs++);
    }
}

int main(void) {
    char **strs;
    char **strs2;
    int i;

    strs = malloc(sizeof(char *) * 10);
    strs2 = malloc(sizeof(char *) * 10);
    strs[9] = NULL;
    i = 0;
    while (i < 9){
        strs[i] = malloc(sizeof(char) * 20);
        strs2[i] = strs[i];
        i++;
    }
    free_strs(strs);
    free_strs(strs2);
    return 0;
}