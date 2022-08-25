#include <stdlib.h>
#include <signal.h>

int arg;
int res;
extern int get_exit_status(int k); //test-defined

extern int try_function(void); //test-defined
extern void catch_function(int sig); //test-defined

extern int catch_me(int (*try_action)(void), void (*catch_action)(int)); // student-defined

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        return 2;
    }

    arg = atoi(argv[1]);

    int k = catch_me(&try_function, &catch_function); // student-defined

    return get_exit_status(k);
}
