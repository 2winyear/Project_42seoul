#include <setjmp.h>
#include <signal.h>

extern jmp_buf env;

static void _on_catch(int sig)
{
    longjmp(env, sig);
}

void register_catch(void)
{
    signal(SIGSEGV, &_on_catch); //11
    signal(SIGFPE, &_on_catch); //8
    signal(SIGPIPE, &_on_catch); //13
    signal(SIGABRT, &_on_catch); //6
    signal(SIGBUS, &_on_catch); //10
}
