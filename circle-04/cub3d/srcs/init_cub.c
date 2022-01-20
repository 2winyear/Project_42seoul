/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 02:59:39 by seungyel          #+#    #+#             */
/*   Updated: 2021/05/24 18:27:29 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_dot_cub(char *filename)
{
	int i;

	i = 0;
	while (filename[i] != '\0')
	{
		if (filename[i + 0] == '.' &&
			filename[i + 1] == 'c' &&
			filename[i + 2] == 'u' &&
			filename[i + 3] == 'b' &&
			filename[i + 4] == '\0')
			return ;
		i++;
	}
	ft_exit(0, 1);
}

void	init(void)
{
	int i;

	g_model.sprites = NULL;
	g_model.real_map = NULL;
	g_model.map = NULL;
	g_model.col = 0;
	g_model.row = 0;
	i = 0;
	while (i < 8)
		g_model.op_flags[i++] = 0;
}

void	read_cub(int fd)
{
	char	op_str[3];
	char	*line;
	int		gnl_flag;
	int		map_flag;
	int		i;

	gnl_flag = 1;
	g_model.player_flag = 0;
	map_flag = 0;
	while (gnl_flag == 1)
	{
		gnl_flag = get_next_line(fd, &line);
		if (gnl_flag == -1)
			ft_exit(0, 1);
		if (line[0] == '\0')
		{
			if (map_flag == 1)
				ft_exit(0, 1);
			free(line);
			continue ;
		}
		i = read_option(line, op_str);
		map_flag = process_line(op_str, &line, i, map_flag);
		free(line);
	}
}

void	parse(char *filename)
{
	const int fd = open(filename, O_RDONLY);

	if (fd == -1)
		ft_exit(0, 1);
	read_cub(fd);
	check_cub();
	allocate_map();
	parse_map();
	check_map(g_model.player_location_y, g_model.player_location_x);
	if (g_model.player_flag != 1)
		ft_exit(0, 1);
}

void	parse_cub(char *filename)
{
	check_dot_cub(filename);
	init();
	parse(filename);
	rewind_map();
}
