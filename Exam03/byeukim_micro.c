#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <math.h>

typedef struct	s_zone
{
	int		width;
	int		height;
	char	word;
}	t_zone;

typedef struct	s_draw
{
	char	type;
	float	x;
	float	y;
	float	width;
	float	height;
	char	word;
}	t_draw;

int	ft_strlen(char *s)
{
	int	idx;

	idx = -1;
	while (s[++idx])
		;
	return (idx);
}

int	exit_str(FILE *file, char **result, char *str)
{
	if (file)
		fclose(file);
	if (*result)
		free(*result);
	write(1, str, ft_strlen(str));
	return (1);
}

char	*get_zone(FILE *file, t_zone *zone)
{
	char	*result;

	if (fscanf(file, "%d %d %c\n", &(zone->width), &(zone->height), &(zone->word)) != 3)
		return (NULL);
	else if (zone->width > 300 || zone->width <= 0 || zone->height > 300 || zone->height <= 0)
		return (NULL);
	result = malloc(sizeof(char) * ((zone->width * zone->height) + 1));
	if (!result)
		return (NULL);
	memset(result, zone->word, zone->width * zone->height);
	return (result);
}

void	draw_now(char *result, t_zone zone)
{
	int	idx;

	idx = -1;
	while (++idx < zone.height)
	{
		write(1, result + (idx * zone.width), zone.width);
		write(1, "\n", 1);
	}
}

int	in_ract(float x, float y, t_draw *draw)
{
	if ((x >= draw->x) && (x <= draw->x + draw->width)
			&& (y >= draw->y) && (y <= draw->y + draw->height))
	{
		if (x - draw->x < 1.f || ((draw->x + draw->width) - x < 1.f) 
				|| (y - draw->y < 1.f) || ((draw->y + draw->height) - y < 1.f))
			return (2);
		return (1);
	}
	return (0);
}

void	draw_shape(char **result, t_draw *draw, t_zone *zone)
{
	int	x;
	int	y;
	int	is_it;

	y = -1;
	while (++y < zone->height)
	{
		x = -1;
		while (++x < zone->height)
		{
			is_it = in_ract((float)x, (float)y, draw);
			if ((draw->type == 'r' && is_it == 2) || (draw->type == 'R' && is_it))
				(*result)[(y * zone->height) + x] = draw->word;
		}
	}
}

int	get_draw(FILE *file, char **result, t_zone *zone)
{
	int		error;
	t_draw	draw;

	while ((error = fscanf(file, "%c %f %f %f %f %c\n", &draw.type, &draw.x, &draw.y, &draw.width, &draw.height, &draw.word) == 6))
	{
		if (draw.width <= 0.f || draw.height <= 0.f || (draw.type != 'r' && draw.type != 'R'))
			return (0);
		draw_shape(result, &draw, zone);
	}
	if (error == -1)
		return (0);
	return (1);
}

int	main(int argc, char *argv[])
{
	FILE	*file = NULL;
	char	*result = NULL;
	t_zone	zone;

	if (argc != 2)
		return (exit_str(file, &result, "Error: argument\n"));
	else if (!(file = fopen(argv[1], "r")))
		return (exit_str(file, &result, "Error: Operation file corrupted\n"));
	else if (!(result = get_zone(file, &zone)))
		return (exit_str(file, &result, "Error: Operation file corrupted\n"));
	else if (!get_draw(file, &result, &zone))
		return (exit_str(file, &result, "Error: Operation file corrupted\n"));
	draw_now(result, zone);
	free(result);
	fclose(file);
	return (0);
}