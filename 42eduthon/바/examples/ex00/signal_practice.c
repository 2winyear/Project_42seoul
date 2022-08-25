#include <signal.h>
#include <stdlib.h>

static void on_fpe(int sig)
{
    (void)sig;
    exit(42);
}

void register_fpe()
{
    signal(SIGFPE, &on_fpe);
}
