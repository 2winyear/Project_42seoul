/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 23:15:52 by seungyel          #+#    #+#             */
/*   Updated: 2021/05/24 03:57:47 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_file(char *filename, int flag)
{
	int fd;

	fd = open(filename, flag);
	if (fd == -1)
		ft_exit(0, 1);
	close(fd);
}

int		ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

void	parse_map(void)
{
	t_node	*cur;
	int		i;
	int		j;

	j = 0;
	cur = g_model.map;
	while (j < g_model.row)
	{
		i = 0;
		while (cur->value[i] != '\0')
		{
			if (cur->value[i] == 'N' || cur->value[i] == 'E' ||
				cur->value[i] == 'W' || cur->value[i] == 'S')
				input_player_location(i, j, cur->value[i]);
			else if (cur->value[i] == '2')
				input_node_sprite(i, j);
			else if (cur->value[i] == '0')
				g_model.real_map[j][i] = 0;
			else
				g_model.real_map[j][i] = 1;
			i++;
		}
		cur = cur->next;
		j++;
	}
}

int		is_map_symbol(char c)
{
	if (c == '0' || c == ' ' || c == '1' || c == 'E' ||
		c == '2' || c == 'W' || c == 'S' || c == 'N')
		return (1);
	else
		return (0);
}

void	input_option_from_line(int op_symbol, char *line, int i)
{
	if (op_symbol == OP_R)
		option_r(line, i);
	else if (op_symbol == OP_NO)
		option_path(line, i, &g_model.no_path);
	else if (op_symbol == OP_SO)
		option_path(line, i, &g_model.so_path);
	else if (op_symbol == OP_WE)
		option_path(line, i, &g_model.we_path);
	else if (op_symbol == OP_EA)
		option_path(line, i, &g_model.ea_path);
	else if (op_symbol == OP_S)
		option_path(line, i, &g_model.s_path);
	else if (op_symbol == OP_F)
		option_color(line, i, g_model.f_color);
	else if (op_symbol == OP_C)
		option_color(line, i, g_model.c_color);
	else
		ft_exit(0, 1);
}
