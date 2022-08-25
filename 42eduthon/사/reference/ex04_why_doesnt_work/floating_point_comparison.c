#include <stdio.h>

int main(void){
    float f;
    int i;

    f = 0;
    i = 0;
    while (i < 10) {
        f += 0.3f;
        i++;
    }
    if (f == 3) {
        printf ("f == 3\n");
    }
    else {
        printf ("f != 3\n");
    }
    return (0);
}