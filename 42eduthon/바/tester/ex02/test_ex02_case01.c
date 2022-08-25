#include <signal.h>

extern int arg;
extern int res;

int get_exit_status(int k)
{
    if (!res)
        // try로 끝나지 않음.
        return 1;
    if (k != arg)
        // try_function으로 끝나지 않음.
        return 1;

    return 0;
}

int try_function(void)
{
    res = 1;
    return arg;
}

void catch_function(int sig)
{
    (void)&sig;
    res = 0;
}
