#include <signal.h>

extern int arg;
extern int res;

int get_exit_status(int k)
{
    if (!res)
        // 요구되는 시그널 캐치에 도달하지 못함.
        return 1;
    if (k != -1)
        // catch_function으로 끝나지 않음.
        return 1;

    return 0;
}

int try_function(void)
{
    res = 0;
    raise(arg);
    return 0;
}

void catch_function(int sig)
{
    if (sig == arg)
    {
        res = 1;
    }
}
