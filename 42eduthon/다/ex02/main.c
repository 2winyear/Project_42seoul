#include <stdio.h>
#include "lib/libft.h"

struct menu{
    char *appetizer;
    char *main;
    char *disert;
};

int read_file(char *file_path, struct menu* read_menu)
{
    int open_file = open(file_path, O_RDONLY);
    if (open_file == -1)
        return -1;

    char *line;
    char **split;

    while (get_next_line(open_file, &line))
    {   
        split = ft_split(line, ':');
        if (!strcmp("에피타이저", split[0]))
            read_menu->appetizer = ft_strdup(split[1]);
        else if (!strcmp("메인", split[0]))
            read_menu->main = ft_strdup(split[1]);
        else if (!strcmp("디저트", split[0]))
            read_menu->disert = ft_strdup(split[1]);
        else
            return -1;
    }

    split = ft_split(line, ':');
    if (!strcmp("에피타이저", split[0]))
        read_menu->appetizer = ft_strdup(split[1]);
    else if (!strcmp("메인", split[0]))
        read_menu->main = ft_strdup(split[1]);
    else if (!strcmp("디저트", split[0]))
        read_menu->disert = ft_strdup(split[1]);
    else
        return -1;
    free(line);
    all_free(split);
    close(open_file);

    return 0;
}

int main(int ac, char **av){
    if (ac != 4)
        return 1;

    struct menu first_menu;
    struct menu second_menu;
    struct menu today_menu;
    
    if (read_file(av[1], &first_menu) == -1)
        return 1;
    if (read_file(av[2], &second_menu) == -1)
        return 1;
    if (read_file(av[3], &today_menu) == -1)
        return 1;

    int write_file = open("out_file", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (write_file == -1)
        return 1;

    printf("%s %s %s\n", first_menu.appetizer, first_menu.main, first_menu.disert);
    printf("%s %s %s\n", second_menu.appetizer, second_menu.main, second_menu.disert);
    printf("%s %s %s\n", today_menu.appetizer, today_menu.main, today_menu.disert);

    // 사용자 작성 부분

    //

}