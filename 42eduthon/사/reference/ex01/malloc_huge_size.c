#include <stdlib.h>
#include <limits.h>

int main(void) {
    int *arr;

    arr = malloc(sizeof(int) * UINT_MAX * 6000000);
    return (0);
}