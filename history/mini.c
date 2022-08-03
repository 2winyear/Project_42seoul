#include "./mini.h"

int print_error(int err_code)
{
    if (err_code == 0)
        write(1, "argu error", 10);
    if (err_code == 1)
        write(1, "file error", 10);
    return (-1);
}

void    init_mine(t_mine *mine)
{
    mine->width = 0;
    mine->height = 0;
    mine->char_arr = NULL;
    mine->char_to_print = '\0';
}

int read_file(FILE **op_file, char *file_name)
{
    *op_file = fopen(file_name, "r");
    if (*op_file == NULL)
        return (-1);
    return (1);
}

int put_mine(t_mine *mine, FILE *op_file)
{
    int result = 0;
    char next_char = '\0';

    if (fscanf(op_file, "%d %d %c", &mine->width, &mine->height, &mine->char_to_print) == 3)
    {
        result = fscanf(op_file, "%c", &next_char);
        if (result == EOF || (next_char == '\n' && result == 1))
        {
            if (mine->width <= 0 || mine->height <= 0 || mine->width > 300 || mine->height > 300)
                return (-1);
            mine->char_arr = malloc(sizeof(char) * (mine->height * mine->width));
            memset(mine->char_arr, mine->char_to_print, mine->height * mine->width);
        }
        else
            return (-1);
    }
    return (1);
}

int check_pixel_in_boarder(float x, float y, t_circle *circle)
{
    float distance;
    
    distance = sqrtf(powf(x - circle->x, 2) + powf(y - circle->y, 2));
    if ( circle->radius - distance < (float)1 )
        return (1);
    return (0);
}

int check_pixel_in_circle(float x, float y, t_circle *circle) // 거리 계산 distance <= circle->radius인 경우. return 1
{
    float distance;
    
    distance = sqrtf(powf(x - circle->x, 2) + powf(y - circle->y, 2));
    if ( distance <= circle->radius)
        return (1);
    return (0);
}

int store_curr_circle_data(t_mine *mine, t_circle *circle)
{
    int x;
    int y;

    y = 0;
    if (circle->radius <= 0) //에러처리
        return (-1);
    while ( y < mine->height)
    {
        x = 0;
        while ( x < mine->width)
        {
            if (check_pixel_in_circle(x, y, circle) == 1) // 거리 계산해서 그릴지 말지 계산
            {
                if (circle->type == 'C' || check_pixel_in_boarder(x, y, circle) == 1) // 만약에 'C'인 경우 채워진 원.
                    mine->char_arr[ y * mine->width + x] = circle->char_to_print;
            }
            x++;
        }
        y++;
    }
    return (1);
}

int put_circle(t_mine *mine, FILE *op_file)
{
    t_circle circle;
    int result = 0;
    char next_char = '\0';

    while ((result = fscanf(op_file, "%c %f %f %f %c", &circle.type, &circle.x, &circle.y, &circle.radius, &circle.char_to_print)) == 5)
    {
        result = fscanf(op_file, "%c", &next_char);
        if (result == EOF || (result == 1 && next_char == '\n'))
        {
            if(store_curr_circle_data(mine, &circle) == -1) // circle 데이터 관련
            {
                return (-1);
            }
        }
        else
            return (-1);
    }
    if (result != EOF && circle.type != '\n')
        return (-1);
    return (1);
}

void drawing_time (t_mine *mine)
{
    int x;

    x=0;
    while(x < mine->width * mine->height)
    {
        write(1, mine->char_arr + x, mine->width);
        x += mine->width;
        write(1, "\n", 1);
    }
}

int main(int argc, char **argv)
{
    FILE *op_file;
    t_mine mine;

    if (argc == 2)
    {
        init_mine(&mine);
        if (read_file(&op_file, argv[1]) == -1)
            print_error(1);
        if (put_mine(&mine, op_file) == -1) //배경 채우기 struct mine
            print_error(1);
        if (put_circle(&mine, op_file) == -1) // circle
            print_error(1);
        drawing_time(&mine);
    }
    else
        return print_error(0);
    return (0);
}
