#include <sys/uio.h>
#include <stdlib.h>
#include <string.h>

#define LEN 2
#define TOTAL 8192
#define IOVECS 256
int main() {
    char yes[LEN] = {'y', '\n'};
    char *buf = malloc(TOTAL);
    int bufused = 0;
    int i;
    struct iovec iov[IOVECS];
    while (bufused < TOTAL) {
        memcpy(buf+bufused, yes, LEN);
        bufused += LEN;
    }
    for (i = 0; i < IOVECS; i++) {
        iov[i].iov_base = buf;
        iov[i].iov_len = TOTAL;
    }
    while(writev(1, iov, IOVECS));
    return 0;
}
