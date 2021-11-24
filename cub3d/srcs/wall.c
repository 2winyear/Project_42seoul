/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 19:20:51 by seungyel          #+#    #+#             */
/*   Updated: 2021/07/04 21:39:14 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_wall(t_calc_wall *cw, t_info *info)
{
	cw->map_x = (int)info->p_x;
	cw->map_y = (int)info->p_y;
	cw->d_x = fabs(1 / cw->r_dir_x);
	cw->d_y = fabs(1 / cw->r_dir_y);
	if (cw->r_dir_x < 0)
	{
		cw->step_x = -1;
		cw->s_dist_x = (info->p_x - cw->map_x) * cw->d_x;
	}
	else
	{
		cw->step_x = 1;
		cw->s_dist_x = (cw->map_x + 1.0 - info->p_x) * cw->d_x;
	}
	if (cw->r_dir_y < 0)
	{
		cw->step_y = -1;
		cw->s_dist_y = (info->p_y - cw->map_y) * cw->d_y;
	}
	else
	{
		cw->step_y = 1;
		cw->s_dist_y = (cw->map_y + 1.0 - info->p_y) * cw->d_y;
	}
}

static void	calc_line_height(t_calc_wall *cw, t_info *info)
{
	while (cw->hit == 0)
	{
		if (cw->s_dist_x < cw->s_dist_y)
		{
			cw->s_dist_x += cw->d_x;
			cw->map_x += cw->step_x;
			cw->side = 0;
		}
		else
		{
			cw->s_dist_y += cw->d_y;
			cw->map_y += cw->step_y;
			cw->side = 1;
		}
		if (g_world_map[cw->map_x][cw->map_y] > 0)
			cw->hit = 1;
	}
	if (cw->side == 0)
		cw->p_w_dist = (cw->map_x - info->p_x + (1 - cw->step_x)
		/ 2) / cw->r_dir_x;
	else
		cw->p_w_dist = (cw->map_y - info->p_y + (1 - cw->step_y)
		/ 2) / cw->r_dir_y;
	cw->l_h = (int)(g_model.height / cw->p_w_dist);
}

static void	init_tex(t_calc_wall *c, t_info *info)
{
	if (c->side == 0)
		c->wall_x = info->p_y + c->p_w_dist * c->r_dir_y;
	else
		c->wall_x = info->p_x + c->p_w_dist * c->r_dir_x;
	c->wall_x -= floor(c->wall_x);
	c->tex_x = (int)(c->wall_x * (double)TEX_WIDTH);
	if ((c->side == 0 && c->r_dir_x > 0) || (c->side == 1 && c->r_dir_y < 0))
		c->tex_x = TEX_WIDTH - c->tex_x - 1;
	c->step = 1.0 * TEX_HEIGHT / c->l_h;
	c->tex_pos = (c->draw_s - g_model.height / 2 + c->l_h / 2) * c->step;
	c->y = c->draw_s;
	if (c->side == 0)
	{
		if (c->step_x == 1)
			c->tex_num = 3;
		if (c->step_x == -1)
			c->tex_num = 2;
	}
	if (c->side == 1)
	{
		if (c->step_y == 1)
			c->tex_num = 1;
		if (c->step_y == -1)
			c->tex_num = 0;
	}
}

static void	draw_wall(t_calc_wall *cw, t_info *info, int x)
{
	while (cw->y < cw->draw_e)
	{
		cw->tex_y = (int)cw->tex_pos & (TEX_HEIGHT - 1);
		cw->tex_pos += cw->step;
		cw->color = info->texture[cw->tex_num][TEX_HEIGHT * cw->tex_y
		+ cw->tex_x];
		if (cw->color >= 0)
			info->data1[cw->y * g_model.width + x] = cw->color;
		else if (cw->side == 1)
			info->data1[cw->y * g_model.width + x] = 0x003b00;
		else if (cw->side == 0)
			info->data1[cw->y * g_model.width + x] = 0x007b00;
		cw->y++;
	}
}

void		calc_wall(t_info *info)
{
	t_calc_wall cw;
	int			x;

	x = 0;
	while (x < g_model.width)
	{
		cw.hit = 0;
		cw.cam_x = 2 * x / (double)g_model.width - 1;
		cw.r_dir_x = info->dir_x + info->plane_x * cw.cam_x;
		cw.r_dir_y = info->dir_y + info->plane_y * cw.cam_x;
		init_wall(&cw, info);
		calc_line_height(&cw, info);
		cw.draw_s = -cw.l_h / 2 + g_model.height / 2;
		if (cw.draw_s < 0)
			cw.draw_s = 0;
		cw.draw_e = cw.l_h / 2 + g_model.height / 2;
		if (cw.draw_e >= g_model.height)
			cw.draw_e = g_model.height - 1;
		init_tex(&cw, info);
		draw_wall(&cw, info, x);
		info->z_buf[x] = cw.p_w_dist;
		++x;
	}
}
