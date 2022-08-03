#ifndef MICROSHELL_H
# define MICROSHELL_H
typedef struct      s_vlst
{
    int             type;
    char            **envp;
    char            **args;
    int             size;
    int             pipe[2];
    int             pipe_last[2];
    struct s_vlst   *next;
    struct s_vlst   *prev;
}   t_vlst;
# define END_NEXT 0
# define PIPE_NEXT 1
# define SEMI_NEXT 2
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <string.h>
#endif