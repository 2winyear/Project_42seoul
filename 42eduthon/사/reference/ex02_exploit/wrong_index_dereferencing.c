#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(void) {
    char *str;
    char *errstr;

    errno = ENOENT;
    errstr = strerror(errno);
    str = malloc(sizeof(char) * strlen(errstr));
    strcpy(str, errstr);
    printf("%s\n", str);
    printf("dereferencing index 100000000: %c\n",  str[100000000]);
    return (0);
}