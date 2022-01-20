/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 23:14:27 by seungyel          #+#    #+#             */
/*   Updated: 2021/07/07 16:49:15 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		calc_dist(t_info *info)
{
	t_node_sprite *cur;

	cur = g_model.sprites;
	while (cur != NULL)
	{
		cur->value.dist = ((info->p_x - cur->value.pos_x) *
		(info->p_x - cur->value.pos_x) + (info->p_y - cur->value.pos_y) *
		(info->p_y - cur->value.pos_y));
		cur = cur->next;
	}
}

void		load_image(t_info *info, int *texture, char *path, t_img *img)
{
	int x;
	int y;

	img->img = mlx_xpm_file_to_image(info->mlx, path, &img->img_width,
	&img->img_height);
	if (img->img == NULL)
		ft_exit(0, 1);
	img->data = (int *)mlx_get_data_addr(img->img, &img->bpp,
	&img->size_l, &img->endian);
	y = 0;
	while (y < img->img_height)
	{
		x = 0;
		while (x < img->img_width)
		{
			texture[img->img_width * y + x] = img->data[img->img_width
			* y + x];
			x++;
		}
		y++;
	}
	mlx_destroy_image(info->mlx, img->img);
}

void		input_player_location(int i, int j, int direction)
{
	g_model.real_map[j][i] = 0;
	g_model.player_location_x = i;
	g_model.player_location_y = j;
	g_model.player_flag++;
	g_model.player_direction = direction;
}

void		check_cub(void)
{
	int i;

	i = 0;
	while (i < 8)
	{
		if (g_model.op_flags[i] != 1)
			ft_exit(0, 1);
		i++;
	}
	if (g_model.width <= 0 || g_model.height <= 0)
		ft_exit(0, 1);
	if (g_model.col < 3 || g_model.row < 3)
		ft_exit(0, 1);
}

void		load_texture(t_info *info)
{
	t_img img;
	t_model	model;

	load_image(info, info->texture[0], g_model.no_path, &img);
	load_image(info, info->texture[1], g_model.so_path, &img);
	load_image(info, info->texture[2], g_model.ea_path, &img);
	load_image(info, info->texture[3], g_model.we_path, &img);
	load_image(info, g_gumba_texture, g_model.s_path, &img);
}
