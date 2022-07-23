#include <stdio.h>
#include <unistd.h>

int main() {
    FILE* file;
    int result;
    int num[2];
    char ch;

    file = fopen("./1", "r");
    while ((result = fscanf(file, "%d %d %c", &num[0], &num[1], &ch)) == 3) {
        printf("result = %d\n", result);
    }
    printf("%d %d\n", num[0], num[1]);
    printf("end %d\n", result);
    printf("end %d\n", fscanf(file, "\n\0"));
    printf("end %d\n", fscanf(file, "%\0"));
    printf("end %d\n", fscanf(file, "\n\0"));

}