#include "micro.h"
/*
    ERROR CODE
*/
void init_paint(t_paint *paint)
{
    paint->data_arr = NULL;
    paint->height = 0;
    paint->width = 0;
    paint->print = '\0';
}

void print_error(int error)
{
    if (error == 0)
        write(1, "Error: argument\n", 16);
    else if (error == 1)
        write(1, "Error: Operation file corrupted\n", 32);
}

int open_file(FILE **op_file, char *filename)
{
    *op_file = fopen(filename, "r");
    if (*op_file == NULL)
        return (-1);
    return (0);
}

void fill_rect(t_rect *rect, t_paint *paint)
{
    int w, h;
    
    h = 0;
    while (h < paint->height)
    {
        w = 0;
        while (w < paint->width)
        {
            if (w > rect->x && w < rect->x + rect->xd && h > rect->y && h < rect->y + rect->yd)
                paint->data_arr[paint->width * h + w] = rect->print;
            w++;
        }
        h++;
    }
}

int put_paint(t_paint *paint, FILE *op_file)
{
    if (fscanf(op_file, "%d %d %c\n", &paint->width, &paint->height, &paint->print) == 3)
    {
        if (paint->width > 300 || paint->width <= 0 || paint->height > 300 || paint->height <= 0)
            return (-1);
        paint->data_arr = malloc(sizeof(char) * (paint->height * paint->width));
        memset(paint->data_arr, paint->print, paint->width * paint->height);
        return (0);
    }
    else
        return (-1);
}

int put_rect(t_paint *paint, FILE *op_file)
{
    t_rect rect;
    int ret_code;
    
    ret_code = fscanf(op_file, "%c %f %f %f %f %c\n", &rect.type, &rect.x, &rect.y, &rect.xd, &rect.yd, &rect.print);
    while (ret_code == 6)
    {
        if (rect.xd <= 0 || rect.yd <= 0)
            return (-1);
        if (rect.type == 'R')
            fill_rect(&rect, paint);
        if (rect.type == 'r')
            // empty_rect(&rect, paint);
        ret_code = fscanf(op_file, "%c %f %f %f %f %c\n", &rect.type, &rect.x, &rect.y, &rect.xd, &rect.yd, &rect.print);
    }
    return (0);
}

void drawing_time(t_paint *paint)
{
    int i = 0;

    while (i < paint->height)
    {
        write(1, &paint->data_arr[paint->width * i], paint->width);
        write(1, "\n", 1);
        i++;
    }
}

int main(int argc, char **argv)
{
    FILE *op_file;
    t_paint paint;
    
    if (argc != 2)
    {
        print_error(0);
        return (1);
    }
    init_paint(&paint);
    if (open_file(&op_file, argv[1]) == -1)
    {
        print_error(1);
        return (1);
    }    
    if (put_paint(&paint, op_file) == -1)
    {
        print_error(1);
        return (1);
    }
    if (put_rect(&paint, op_file) == -1)
    {
        print_error(1);
        return (1);
    }
    drawing_time(&paint);
    fclose(op_file);
    return (0);
}