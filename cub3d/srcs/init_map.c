/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 02:59:43 by seungyel          #+#    #+#             */
/*   Updated: 2021/05/24 03:57:04 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		input_map_from_row(char *row)
{
	t_node *new_node;
	t_node *cur;

	g_model.row++;
	new_node = malloc(sizeof(t_node));
	if (new_node == NULL)
		ft_exit(0, 1);
	new_node->value = row;
	new_node->next = NULL;
	if (g_model.map == NULL)
	{
		g_model.map = new_node;
		return ;
	}
	cur = g_model.map;
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = new_node;
}

void		input_map_from_line(char *line)
{
	int		col_count;
	int		i;
	char	*row;

	col_count = 0;
	i = 0;
	while (line[i] != '\0')
	{
		if (is_map_symbol(line[i++]) == 1)
			col_count++;
		else
			ft_exit(0, 1);
	}
	if (g_model.col < col_count)
		g_model.col = col_count;
	if ((row = malloc(sizeof(char) * (col_count + 1))) == NULL)
		ft_exit(0, 1);
	i = 0;
	while (line[i] != '\0')
	{
		row[i] = line[i];
		i++;
	}
	row[i] = '\0';
	input_map_from_row(row);
}

int			allocate_map(void)
{
	int i;

	g_model.real_map = malloc(sizeof(char *) * g_model.row);
	if (g_model.real_map == NULL)
		ft_exit(0, 1);
	g_model.real_map[0] = malloc(sizeof(char) * g_model.row * g_model.col);
	if (g_model.real_map[0] == NULL)
		ft_exit(0, 1);
	i = 0;
	while (i < g_model.row)
	{
		g_model.real_map[i] = g_model.real_map[0] + g_model.col * i;
		i++;
	}
	return (1);
}

void		check_map(int r, int c)
{
	if (g_model.real_map[r][c] == 1 ||
		g_model.real_map[r][c] == CHECKED_ROAD)
		return ;
	if (r == 0 || r == g_model.row - 1 || c == 0 || c == g_model.col - 1)
		ft_exit(0, 1);
	if (g_model.real_map[r][c] == 0)
		g_model.real_map[r][c] = CHECKED_ROAD;
	check_map(r, c - 1);
	check_map(r, c + 1);
	check_map(r + 1, c);
	check_map(r - 1, c);
}

void		rewind_map(void)
{
	int i;
	int j;

	j = 0;
	while (j < g_model.row)
	{
		i = 0;
		while (i < g_model.col)
		{
			if (g_model.real_map[j][i] == CHECKED_ROAD)
				g_model.real_map[j][i] = 0;
			i++;
		}
		j++;
	}
}
