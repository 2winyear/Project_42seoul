#include "mini.h"

int print_error(int error)
{
    if (error == 0)
        write(1, "Error: argument\n", 16);
    if (error == 1)
        write(1, "Error: Operation file corrupted\n", 32);
    return (1);
}

void init_paint(t_paint *paint)
{
    paint->width = 0;
    paint->height = 0;
    paint->data_arr = NULL;
    paint->print = '\0';
}

int open_file(char *filename, FILE **op_file)
{
    *op_file = fopen(filename, "r");
    if (*op_file == NULL)
        return (-1);
    return (0);
}

int put_paint(t_paint *paint, FILE *op_file)
{
    int ret_code = 0;
    
    if (fscanf(op_file, "%d %d %c\n", &paint->width, &paint->height, &paint->print) == 3)
    {
        if (paint->width > 300 || paint->width <= 0 || paint->height > 300 || paint->height <= 0)
            return (-1);
        paint->data_arr = malloc(sizeof(char) * (paint->width * paint->height));
        memset(paint->data_arr, paint->print, paint->height * paint->width);
        return (0);
    }
    else
        return (-1);
}

int first_if(float x, float y, t_circle *circle)
{
    float dist = sqrtf(powf(x - circle->x, 2.f) + powf(y - circle->y, 2.f));

    if (dist <= circle->radius)
        return (1);
    return (0);
}

int second_if(float x, float y, t_circle *circle)
{
    float dist = sqrtf(powf(x - circle->x, 2.f) + powf(y - circle->y, 2.f));

    if (circle->radius - dist < (float)1)
        return (1);
    return (0);
}

int store_in_circle(t_paint *paint, t_circle *circle)
{
    int w, h;

    if (circle->radius <= 0)
        return (-1);
    h = 0;
    while (h < paint->height)
    {
        w = 0;
        while (w < paint->width)
        {
            if (first_if(w, h, circle) == 1)
            {
                if (circle->type == 'C')
                    paint->data_arr[h * paint->width + w] = circle->print;
                if (circle->type == 'c' && second_if(w, h, circle) == 1)
                    paint->data_arr[h * paint->width + w] = circle->print;
            }
            w++;
        }
        h++;
    }
    return(0);
}

int put_circle(t_paint *paint, FILE *op_file)
{
    t_circle circle;
    int ret_code = 0;
    
    ret_code = fscanf(op_file, "%c %f %f %f %c\n", &circle.type, &circle.x, &circle.y, &circle.radius, &circle.print);
    while (ret_code == 5)
    {
        if (store_in_circle(paint, &circle) == -1)
            return (-1);
        ret_code = fscanf(op_file, "%c %f %f %f %c\n", &circle.type, &circle.x, &circle.y, &circle.radius, &circle.print);
    }
    if (ret_code != EOF)
        return (-1);
    return (0);
}

void drawing_time(t_paint *paint)
{
    int i = 0;
    
    while (i < paint->height)
    {
        write(1, &paint->data_arr[i * paint->width], paint->width);
        write(1, "\n", 1);
        i++;
    }
}

int main(int argc, char **argv)
{
    FILE *op_file;
    t_paint paint;
    
    if (argc != 2)
        return(print_error(0));

    init_paint(&paint);
    if (open_file(argv[1], &op_file) == -1)
        return (print_error(1));
    if (put_paint(&paint, op_file) == -1)
        return (print_error(1));
    if (put_circle(&paint, op_file) == -1)
        return (print_error(1));
    fclose(op_file);
    drawing_time(&paint);
    free(paint.data_arr);

    return (0);
}