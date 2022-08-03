#include "jihokim_micro.h"
#include <stdio.h>

int     ft_strlen(char *str)
{
    int     len;
    if (!str)
        return (0);
    len = 0;
    while (str[len])
        len++;
    return (len);
}
int     ft_perror(char *str)
{
    int     len;
    len = ft_strlen(str);
    write(2, str, len);
    write(2, "\n", 1);
    return (len);
}
void    fatal_error(char *str)
{
    ft_perror(str);
    exit(1);
}
void    error_execfail(char *cmd)
{
    char    *msg;
    msg = "error: cannot execute ";
    write(2, msg, ft_strlen(msg));
    write(2, cmd, ft_strlen(cmd));
    write(2, "\n", 1);
}
/*
 *  vlist utils
 */
t_vlst  *vlst_init(char **envp)
{
    t_vlst      *new;
    new = malloc(sizeof(t_vlst));
    if (!new)
        return (0);
    new->type = 0;
    new->envp = envp;
    new->args = 0;
    new->size = 0;
    new->pipe[0] = -1;
    new->pipe[1] = -1;
    new->prev = 0;
    new->next = 0;
    return (new);
}
void    vlst_clear(t_vlst **vlst)
{
    t_vlst      *head;
    t_vlst      *tmp;
    head = *vlst;
    while (head)
    {
        tmp = head->next;
        free(head);
        head = tmp;
    }
}
/*
 * args into list
 */
void    vlst_set_to_pipe(t_vlst **vlst)
{
    t_vlst      *this;
    t_vlst      *new;
    this = *vlst;
    this->type = PIPE_NEXT;
    if (pipe(this->pipe) == -1)
        fatal_error("error: fatal1");
    new = vlst_init(this->envp);
    this->next = new;
    new->prev = this;
    *vlst = new;
}
void    vlst_set_to_semi(t_vlst **vlst)
{
    t_vlst      *this;
    t_vlst      *new;
    this = *vlst;
    this->type = SEMI_NEXT;
    new = vlst_init(this->envp);
    this->next = new;
    new->prev = this;
    *vlst = new;
}
static void args_copy(char **arr1, char **arr2, int size)
{
    int     i;
    i = 0;
    while (i < size)
    {
        arr1[i] = arr2[i];
        i++;
    }
}
void        vlst_args_push(t_vlst *vlst, char **avp)
{
    char    **new;
    new = malloc(sizeof(char *) * (vlst->size + 2));
    if (!new)
        fatal_error("error: fatal2");
    args_copy(new, vlst->args, vlst->size);
    new[vlst->size] = *avp;
    vlst->size++;
    new[vlst->size] = 0;
    free(vlst->args);
    vlst->args = new;
}
int args_readin(t_vlst **vars, int ac, char **av, char **envp)
{
    int     i;
    *vars = vlst_init(envp);
    i = 0;
    while (i < ac)
    {
        if (!strcmp(av[i], "|"))
            vlst_set_to_pipe(vars);
        else if (!strcmp(av[i], ";"))
            vlst_set_to_semi(vars);
        else
            vlst_args_push(*vars, av + i);
        i++;
    }
    (*vars)->type = END_NEXT;
    return i;
}
/*
 * built-in
 */
int     builtin_cd(t_vlst *vlst)
{
    if (vlst->size != 2)
        write(2, "error: cd: bad arguments\n", ft_strlen("error: cd: bad arguments\n"));
    if (chdir(vlst->args[1]) == -1)
        write(2, "error: cd: cannot change directory to path_to_change\n", ft_strlen("error: cd: cannot change directory to path_to_change\n"));
    return (0);
}
/*
 * shell
 */
void    child_setup(t_vlst *vlst)
{
    t_vlst      *prev;
    prev = vlst->prev;
    if (prev && prev->type == PIPE_NEXT)
        dup2(prev->pipe[0], 0);
    if (vlst->type == PIPE_NEXT)
        dup2(vlst->pipe[1], 1);
}
void    parent_cleanup(t_vlst *vlst)
{
    t_vlst      *prev;
    prev = vlst->prev;
    if (prev && prev->type == PIPE_NEXT)
        close(prev->pipe[0]);
    if (vlst->type == PIPE_NEXT)
        close(vlst->pipe[1]);
}
int     command_execution(t_vlst *vlst)
{
    int     child;
    int     stat;
    child = fork();
    if (child == -1)
        fatal_error("error: fatal3");
    if (child == 0)
    {
        child_setup(vlst);
        execve(vlst->args[0], vlst->args, vlst->envp);
        error_execfail(vlst->args[0]);
    }
    else if (waitpid(child, &stat, 0) < 0)
        fatal_error("error: fatal4");
    parent_cleanup(vlst);
    return (WEXITSTATUS(stat));
}
int microshell_processor(t_vlst *vlst)
{
    int     ret;
    while (vlst != 0)
    {
        printf("hi\n");
        if (!strcmp(vlst->args[0], "cd"))
            ret = builtin_cd(vlst);
        else
            ret = command_execution(vlst);
        vlst = vlst->next;
    }
    return (ret);
}

int main(int argc, char **argv, char **envp)
{
    t_vlst      *vars;
    int         ret;
    if (argc == 1)
        return (0);
    args_readin(&vars, argc - 1, argv + 1, envp);
    ret = microshell_processor(vars);
    vlst_clear(&vars);
    return (ret);
}