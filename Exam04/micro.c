#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>

#define READ 0
#define WRITE 1

void ft_print_error(char *msg)
{
    int i = 0;

    while (msg[i])
        i++;
    write(2, msg, i);
}

int ft_execve(char **argv, int i, char **envp)
{
    argv[i] = NULL;
    execve(argv[0], argv, envp);
    ft_print_error("error : cannot execute ");
    ft_print_error(argv[0]);
    ft_print_error("\n");
    return (1);
}

int main(int argc, char **argv, char **envp)
{
    (void) argc;
    int pid;
    int fd[2];
    int temp_fd = dup(STDIN_FILENO);
    int i = 0;

    while (argv[i] && argv[i + 1])
    {
        argv = &argv[i + 1];
        i = 0;
        while (argv[i] && strcmp(argv[i], ";") && strcmp(argv[i], "|"))
            i++;
        if(!strcmp(argv[0], "cd"))
        {
            if (i != 2) //error
                ft_print_error("error: cd: bad arguments\n");
            else if (chdir(argv[1]) != 0)
            {
                ft_print_error("error : cd: cannot change directory to ");
				ft_print_error(argv[1]);
				ft_print_error("\n");
            }
        }
        else if (i && (argv[i] == NULL || !strcmp(argv[i], ";")))
        {
            pid = fork();
            if (pid == 0) //child
            {
                dup2(fd[WRITE], STDIN_FILENO);
                if (ft_execve(argv, i, envp))
                    return (1);
            }
            else
                waitpid(pid, NULL, 0);
                dup2(temp_fd, STDIN_FILENO);
        }
        else if (i && !strcmp(argv[i], "|"))
        {
            pipe(fd);
            pid = fork();
            if (pid == 0)
            {
                dup2(fd[WRITE], STDOUT_FILENO);
                close(fd[WRITE]);
                if (ft_execve(argv, i, envp))
                    return (1);
            }
            else
            {
                close(fd[WRITE]);
                waitpid(pid, NULL, 0);
                dup2(fd[READ], STDIN_FILENO);
                close(fd[READ]);
            }
        }
    }
    close(temp_fd);
    return (0);
}