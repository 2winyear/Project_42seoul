/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_option.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 02:58:50 by seungyel          #+#    #+#             */
/*   Updated: 2021/05/24 19:50:57 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		option_color(char *line, int i, unsigned int *color)
{
	color[R] = 0;
	color[G] = 0;
	color[B] = 0;
	while (line[i] == ' ')
		i++;
	while (ft_isdigit(line[i]) == 1)
		color[R] = color[R] * 10 + line[i++] - '0';
	if (line[i] == ',')
		i++;
	while (ft_isdigit(line[i]) == 1)
		color[G] = color[G] * 10 + line[i++] - '0';
	if (line[i] == ',')
		i++;
	while (ft_isdigit(line[i]) == 1)
		color[B] = color[B] * 10 + line[i++] - '0';
	if (color[R] > 255 || color[G] > 255 || color[B] > 255)
		ft_exit(0, 1);
	while (line[i] != '\0')
		if (ft_isspace(line[i++]) == 0)
			ft_exit(0, 1);
}

void		option_r(char *line, int i)
{
	g_model.width = 0;
	g_model.height = 0;
	while (line[i] == ' ')
		i++;
	while (ft_isdigit(line[i]) == 1)
		g_model.width = g_model.width * 10 + line[i++] - '0';
	while (line[i] == ' ')
		i++;
	while (ft_isdigit(line[i]) == 1)
		g_model.height = g_model.height * 10 + line[i++] - '0';
	while (line[i] != '\0')
		if (ft_isspace(line[i++]) == 0)
			ft_exit(0, 1);
}

void		option_path(char *line, int start, char **path)
{
	int		i;
	int		path_idx;
	char	*new_path;

	while (line[start] == ' ')
		start++;
	i = start;
	path_idx = 0;
	while (line[i] != '\0')
	{
		path_idx++;
		i++;
	}
	check_file(&line[start], O_RDONLY);
	if ((new_path = malloc(sizeof(char) * (path_idx + 1))) == NULL)
		ft_exit(0, 1);
	i = start;
	path_idx = 0;
	while (line[i] != '\0')
	{
		new_path[path_idx] = line[i++];
		path_idx++;
	}
	new_path[path_idx] = '\0';
	*path = new_path;
}

int			read_option(char *line, char *op_str)
{
	int i;
	int op_idx;

	i = 0;
	op_idx = 0;
	while (line[i] == ' ')
		i++;
	while (ft_isupper(line[i]) == 1)
	{
		if (op_idx >= 2)
		{
			ft_exit(0, 1);
		}
		op_str[op_idx] = line[i];
		op_idx++;
		i++;
	}
	op_str[op_idx] = '\0';
	return (i);
}

int			is_option_symbol(char *str)
{
	if (ft_strcmp(str, "R") == 0)
		return (OP_R);
	else if (ft_strcmp(str, "NO") == 0)
		return (OP_NO);
	else if (ft_strcmp(str, "SO") == 0)
		return (OP_SO);
	else if (ft_strcmp(str, "WE") == 0)
		return (OP_WE);
	else if (ft_strcmp(str, "EA") == 0)
		return (OP_EA);
	else if (ft_strcmp(str, "S") == 0)
		return (OP_S);
	else if (ft_strcmp(str, "F") == 0)
		return (OP_F);
	else if (ft_strcmp(str, "C") == 0)
		return (OP_C);
	else
		return (0);
}
