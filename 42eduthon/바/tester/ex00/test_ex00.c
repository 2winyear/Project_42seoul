#include <signal.h>
#include <string.h>

void register_fpe();

static void raise_fpe(void)
{
    const int life = 42;
    int everything = life ^ life;
    int answer;

    answer = life / everything;
}

int main(int ac, char* av[])
{
    if (ac > 1 && !strcmp(av[1], "catch"))
        register_fpe();
    raise_fpe();
    return 99;
}
