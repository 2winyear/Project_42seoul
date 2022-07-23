#include "2_mini.h"

int store_curr_circle_data(t_mine *zone, t_circle *circle)
{
    int x;
    int y;

    y = 0;
    if (circle->radius <= 0)
        return (-1);
    while (y < zone->height)
    {
        x = 0;
        while (x < zone->width)
        {
            if (check_if_pixel_in_circle(x, y, circle) == 1) 
            {
                if (circle->type == 'C' || check_if_pixel_in_boarder(x,y,circle) == 1)
                {   
                    zone->data_arr[(y * zone->width) + x] = circle->char_to_print;
                }
            }
            x++;
        }
        y++;
    }
    return (1);
}

int get_circle_data(FILE *op_file, t_mine *mine) 
{
    t_circle circle;
    char char_following = '\0';
    int ret_code = 0;

    while ((ret_code = fscanf(op_file, "%c %f %f %f %c", &circle.type, &circle.x, &circle.y, &circle.radius, &circle.char_to_print)) == 5)
    {
        ret_code = fscanf(op_file, "%c", &char_following);
        if (ret_code == EOF || (ret_code == 1 && char_following == '\n'))
        {
            if (store_curr_circle_data(mine, &circle) == -1)
            {
                return (-1);
            }
        }
        else
            return (-1);
    }
    if (ret_code != EOF && circle.type != '\n')
        return (-1);
    return (1);
}