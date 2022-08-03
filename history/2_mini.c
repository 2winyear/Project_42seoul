#include "./2_mini.h"

int open_file(char* file_name, FILE **op_file)
{
	*op_file = fopen(file_name, "r");
	if (*op_file == NULL)
		return (-1);
	return(1);
}


void init_mine(t_mine *mine)
{
	mine->width = 0;
	mine->height = 0;
	mine->char_to_print='\0';
	mine->data_arr=NULL;
}

int return_print(int result)
{
	if (result == 1)
		write(1, "input_error", 11);
	if (result == 0)
		write(1, "error", 5);
	return(-1);
}

int check_if_pixel_in_circle(int x, int y, t_circle *circle)
{
	float distance;

	distance = sqrtf(powf(x - circle->x, 2) + powf(y - circle->y, 2));
	if (circle->radius < distance)
		return (1);
	return (0);
}

int check_if_pixel_in_board(int x, int y, t_circle *circle)
{
	float distance;
	
	distance = sqrtf(powf(x - circle->x ,2) + powf(y - circle->y, 2));
	if (circle->type - distance < 1)
		return (1);
	return (0);
}

int store_curr_in_circle(t_mine *mine, t_circle *circle)
{
	int x;
	int y;

	if (circle->radius <= 0)
		return (-1);
	y = 0;
	while ( y < mine->height)
	{
		x = 0;
		while ( x < mine->width )
		{
			if (check_if_pixel_in_circle(x,y,circle) == 1)
			{
				if (circle->type == 'C' || check_if_pixel_in_board(x,y,circle) == 1)
				{	
					mine->data_arr[(y * mine->height) + x]	= circle->char_to_print;
				}
			}
			x++;		
		}
		y++;
	}
	return (0);
}

int get_input_circle(t_mine *mine, FILE *op_file)
{
	t_circle circle;
	char following_char = '\0';
	int ret_code = 0;

	while ((ret_code = fscanf(op_file, "%c, %f, %f, %f, %c", &circle.type, &circle.x, &circle.y, &circle.radius, &circle.char_to_print)) == 5)
	{
		ret_code = fscanf(op_file, "%c", &following_char);
		if (ret_code == EOF || (following_char == '\n' && ret_code == 1))
		{
			if (store_curr_in_circle(mine, &circle) == -1)
				return (-1);
		}
		else
			return (-1);
	}
	return (0);
}

int get_input_data(t_mine *mine, FILE *op_file)
{
	char following_char = '\0';
	int ret_code = 0;

	if ((ret_code = fscanf(op_file, "%d %d %c", &mine->width, &mine->height, &mine->char_to_print)) == 3)
	{
		ret_code = fscanf(op_file, "%c", &following_char);
		if (ret_code == EOF || (following_char == '\n' && ret_code == 1))
			if (mine->width <= 0 || mine->height > 300 || mine->height <= 0 || mine->width > 300)
				return (-1);
		mine->data_arr = malloc(sizeof(char) * (mine->width * mine->height));
		memset(mine->data_arr, mine->char_to_print, mine->width * mine->height);
	}
	else
		return (-1);
	return (1);
}

void drawing_time(t_mine *mine)
{
    int x;

    x = 0;
    while (x < mine->width * mine->height)
    {
        write(1, mine->data_arr + x, mine->width);
        x += mine->width;
        write(1, "\n", 1);
    }
}

int main(int argc, char **argv)
{
	t_mine mine;
	FILE *op_file;
	
	if (argc == 2)
	{
		init_mine(&mine);
		if (open_file(argv[1], &op_file) == -1)
		{
			return_print(1);
		}
		if (get_input_data(&mine, op_file) == -1)
			return_print(1);
		if (get_input_circle(&mine, op_file) == -1)
			return_print(1);
		drawing_time(&mine);
	}
	else
		return_print(0);
	return (1);
}
