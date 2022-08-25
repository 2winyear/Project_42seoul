#include <setjmp.h>
#include <signal.h>

#include <stdio.h>
#include <stdlib.h>

jmp_buf env;

extern int register_catch(void); // student-defined

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        return 65;
    }

    int sig = atoi(argv[1]);
    register_catch(); // student-defined

    int k = setjmp(env);

    if (k == 0)
    {
        // try block
        raise(sig);
    }
    else
    {
        // catch block
        return k;
    }

    // unreachable code
    return 64;
}
