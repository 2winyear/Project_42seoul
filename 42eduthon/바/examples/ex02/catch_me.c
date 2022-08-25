#include <setjmp.h>
#include <signal.h>
#include <stdio.h>

jmp_buf env;

static void _on_catch(int sig)
{
    longjmp(env, sig);
}

int catch_me(int (*try_action)(void), void (*catch_action)(int))
{
    signal(SIGSEGV, &_on_catch); //11
    signal(SIGFPE, &_on_catch); //8
    signal(SIGPIPE, &_on_catch); //13
    signal(SIGABRT, &_on_catch); //6
    signal(SIGBUS, &_on_catch); //10

    int ret = setjmp(env);
    if (ret == 0)
    {
        // try
        return try_action();
    }
    else
    {
        // catch
        catch_action(ret);
        return -1;
    }
}
