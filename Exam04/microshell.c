// #include <unistd.h>
// #include <string.h>
// #include <sys/wait.h>

// void ft_print_err(char *str)
// {
//     int i = 0;

//     while (str[i])
//         i++;
//     write(2, str, i);
// }

// int ft_execute(char **argv, int i, int temp_fd, char **envp)
// {
//     argv[i] = NULL;
//     close (temp_fd);
//     execve(argv[0], argv, envp);
//     ft_print_err("error : cannot execute ");
// 	ft_print_err(argv[0]);
// 	ft_print_err("\n");
//     return (1);
// }

// int main(int argc, char **argv, char **envp)
// {
//     (void)argv;
//     int fd[2];
//     int i = 0;
//     int pid = 0;
//     int temp_fd = dup(STDIN_FILENO);

//     while (argv[i] && argv[i + 1])
//     {
//         argv = &argv[i + 1];
//         i = 0;
//         while (argv[i] && strcmp(argv[i], ";") && strcmp(argv[i], "|"))
//             i++;

//         //cd errors
//         if (strcmp(argv[0], "cd") == 0)
//         {
//             if (i != 2)
// 				ft_print_err("error: cd: bad arguments\n");
//             else if (chdir(argv[1]) != 0)
//             {
//                 ft_print_err("error : cd: cannot change directory to ");
// 				ft_print_err(argv[1]);
// 				ft_print_err("\n");
//             }
//         }
//         // ";" implementation
//         else if (argv != &argv[i] && (argv[i] == NULL || strcmp(argv[i], ";") == 0))
//         {
//             pid = fork();
//             if (pid == 0)
//             {
//                 dup2(temp_fd, STDIN_FILENO);
//                 if (ft_execute(argv, i, temp_fd, envp))
//                     return (1);
//             }
//             else
//             {
//                 close(temp_fd);
//                 waitpid(-1, NULL, WUNTRACED);
//                 temp_fd = dup(STDIN_FILENO);
//             }
//         }
//         // "|" implementation
//         else if (argv != &argv[i] && strcmp(argv[i], "|") == 0)
//         {
//             pipe(fd);
//             pid = fork();
//             if (pid == 0) 
//             {
//                 dup2(temp_fd, STDIN_FILENO);
//                 dup2(fd[1], STDOUT_FILENO);
//                 close(fd[1]);
//                 close(temp_fd);
//                 if (ft_execute(argv, i, temp_fd, envp))
//                     return (1);
//             }
//             else
//             {
//                 close(temp_fd);
//                 close(fd[1]);
//                 waitpid(-1, NULL, WUNTRACED);
//                 temp_fd = dup(fd[0]);
//                 close(fd[0]);
//             }
//         }
//     }
//     close(temp_fd);
//     return (0);
// }