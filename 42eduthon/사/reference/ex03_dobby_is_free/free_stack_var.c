#include <stdlib.h>
#include <stdio.h>

int main(void) {
    {
        int *a;
        int b;

        // a = malloc(sizeof(int) * 2);
        a = &b;
        free(a);
        // free(a);
    }
    return 0;
}