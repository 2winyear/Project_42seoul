/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 02:58:35 by seungyel          #+#    #+#             */
/*   Updated: 2021/07/07 17:01:25 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		clear(t_info *info)
{
	int i;
	int j;

	i = 0;
	while (i < g_model.width)
	{
		j = 0;
		while (j < (g_model.height / 2))
		{
			info->data1[j * g_model.width + i] = 0;
			info->data1[j * g_model.width + i] |= g_model.c_color[R] << 16;
			info->data1[j * g_model.width + i] |= g_model.c_color[G] << 8;
			info->data1[j * g_model.width + i] |= g_model.c_color[B] << 0;
			j++;
		}
		while (j < g_model.height)
		{
			info->data1[j * g_model.width + i] = 0;
			info->data1[j * g_model.width + i] |= g_model.f_color[R] << 16;
			info->data1[j * g_model.width + i] |= g_model.f_color[G] << 8;
			info->data1[j * g_model.width + i] |= g_model.f_color[B] << 0;
			j++;
		}
		i++;
	}
}


int			main_loop(t_info *info)
{
	clear(info);
	info_press(info, 0);
	calc_wall(info);
	calc_sprite(info);
	mlx_put_image_to_window(info->mlx, info->win, info->img1, 0, 0);
	mlx_put_image_to_window(info->mlx, info->win, info->img2, 0, 0);
	return (0);
}

void		input_player_direction(t_info *info)
{
	if (g_model.player_direction == 'E')
	{
		info->dir_y = 1;
		info->plane_x = 0.66;
		info->plane_y = 0;
	}
	if (g_model.player_direction == 'S')
	{
		info->dir_x = 1;
		info->plane_x = 0;
		info->plane_y = -0.66;
	}
	if (g_model.player_direction == 'N')
	{
		info->dir_x = -1;
		info->plane_x = 0;
		info->plane_y = 0.66;
	}
	if (g_model.player_direction == 'W')
	{
		info->dir_y = -1;
		info->plane_x = -0.66;
		info->plane_y = 0;
	}
}

void	fill_squares(t_info *info, int x, int y, int color)
{
	int col;
	int row;

	row = 0;
	while (row < (int)(MINI_SCALE * TILE_SIZE))
	{
		col = 0;
		while (col < (int)(MINI_SCALE * TILE_SIZE))
		{
			info->data2[(int)(MINI_SCALE * g_model.col * TILE_SIZE) * (y + row) + (x + col)] = color;
			col++;
		}
		row++;
	}
}

void		render_map(t_info *info, t_info *mlx)
{
	int col;
	int row;

	row = 0;
	while (row < g_model.row)
	{
		col = 0;
		while (col < g_model.col)
		{
			if (g_model.real_map[row][col] == 1)
				fill_squares(info, (int)(MINI_SCALE * TILE_SIZE * col), (int)(MINI_SCALE * TILE_SIZE * row), 0xffffff);
			else
				fill_squares(info, (int)(MINI_SCALE * TILE_SIZE * col), (int)(MINI_SCALE * TILE_SIZE * row), 0x000000);
			col++;
		}
		row++;
	}
}

void load_real_map(void)
{
	int i;
	int j;

	i = 0;
	while (i < g_model.row)
	{
		j = 0;
		while (j < g_model.col)
		{
			printf("%d",g_model.real_map[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

void		init_cub3d(t_info *info)
{
	int		t1;
	int		t2;

	input_player_direction(info);
	g_world_map = g_model.real_map;
	info->p_x = g_model.player_location_y + 0.511;
	info->p_y = g_model.player_location_x + 0.51;
	info->m_speed = 0.05;
	info->r_sp = 0.05;
	info->press.k_w = 0;
	info->press.k_a = 0;
	info->press.k_s = 0;
	info->press.k_d = 0;
	info->press.k_ar_r = 0;
	info->press.k_ar_l = 0;
	info->mlx = mlx_init();
	mlx_get_screen_size(info->mlx, &t1, &t2);
	if (g_model.width > t1)
		g_model.width = t1;
	if (g_model.height > t2)
		g_model.height = t2;
	load_texture(info);
	info->win = mlx_new_window(info->mlx, g_model.width, g_model.height, "lsy");
	info->img1 = mlx_new_image(info->mlx, g_model.width, g_model.height);
	info->img2 = mlx_new_image(info->mlx, (int)(MINI_SCALE * g_model.col * TILE_SIZE), (int)(MINI_SCALE * g_model.row * TILE_SIZE));
	info->data1 = (int *)mlx_get_data_addr(info->img1, &g_model.bpp, &t1, &t2);
	info->data2 = (int *)mlx_get_data_addr(info->img2, &g_model.bpp, &t1, &t2);
	render_map(info, info->mlx);
	load_real_map();
}

int			main(int argc, char **argv)
{
	t_info	*info;
	int		flag;

	info = &g_model.info;
	flag = 0;
	if (argc == 3)
	{
		flag = !ft_strcmp(argv[1], "--save");
		if (!flag)
			ft_exit(0, 1);
		parse_cub(argv[2]);
	}
	else if (argc == 2)
		parse_cub(argv[1]);
	else
		ft_exit(0, 1);
	init_cub3d(info);
	if (flag)
		return (save_bmp(info));
	mlx_hook(info->win, X_EVENT_KEY_PRESS, 0, &key_press, info);
	mlx_hook(info->win, X_EVENT_KEY_RELEASE, 0, &key_release, info);
	mlx_hook(info->win, X_EVENT_KEY_EXIT, 0, &ft_memexit, 0);
	mlx_loop_hook(info->mlx, &main_loop, info);
	mlx_loop(info->mlx);
}
