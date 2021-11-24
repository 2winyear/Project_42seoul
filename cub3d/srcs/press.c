/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 23:22:12 by seungyel          #+#    #+#             */
/*   Updated: 2021/05/24 19:01:17 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			process_line(char *op_str, char **line, int i, int map_flag)
{
	int op_symbol;

	op_symbol = is_option_symbol(op_str);
	if (op_symbol >= 0 && g_model.op_flags[op_symbol] == 0 && map_flag == 0)
	{
		input_option_from_line(op_symbol, *line, i);
		g_model.op_flags[op_symbol] = 1;
	}
	else if (is_map_symbol(*line[0]) == 1)
	{
		input_map_from_line(*line);
		map_flag = 1;
	}
	else
		ft_exit(0, 1);
	free(*line);
	*line = NULL;
	return (map_flag);
}

void		info_press_other(t_info *i)
{
	double ox;
	double p_x;

	if (i->press.k_ar_r == 1)
	{
		ox = i->dir_x;
		i->dir_x = i->dir_x * cos(-i->r_sp) - i->dir_y * sin(-i->r_sp);
		i->dir_y = ox * sin(-i->r_sp) + i->dir_y * cos(-i->r_sp);
		p_x = i->plane_x;
		i->plane_x = i->plane_x * cos(-i->r_sp) - i->plane_y * sin(-i->r_sp);
		i->plane_y = p_x * sin(-i->r_sp) + i->plane_y * cos(-i->r_sp);
	}
	if (i->press.k_ar_l == 1)
	{
		ox = i->dir_x;
		i->dir_x = i->dir_x * cos(i->r_sp) - i->dir_y * sin(i->r_sp);
		i->dir_y = ox * sin(i->r_sp) + i->dir_y * cos(i->r_sp);
		p_x = i->plane_x;
		i->plane_x = i->plane_x * cos(i->r_sp) - i->plane_y * sin(i->r_sp);
		i->plane_y = p_x * sin(i->r_sp) + i->plane_y * cos(i->r_sp);
	}
}

void		info_press(t_info *info, int s)
{
	s = info->press.k_w == 1 ? 1 : -1;
	if (info->press.k_w == 1 || info->press.k_s == 1)
	{
		if (!g_world_map[(int)(info->p_x + info->dir_x * info->m_speed * s)]
		[(int)(info->p_y)])
			info->p_x += info->dir_x * info->m_speed * s;
		if (!g_world_map[(int)(info->p_x)][(int)(info->p_y + info->dir_y
		* info->m_speed * s)])
			info->p_y += info->dir_y * info->m_speed * s;
	}
	s = info->press.k_d == 1 ? 1 : -1;
	if (info->press.k_a == 1 || info->press.k_d == 1)
	{
		if (!g_world_map[(int)(info->p_x + info->plane_x * info->m_speed * s)]
		[(int)(info->p_y)])
			info->p_x += info->plane_x * info->m_speed * s;
		if (!g_world_map[(int)(info->p_x)][(int)(info->p_y + info->plane_y
		* info->m_speed * s)])
			info->p_y += info->plane_y * info->m_speed * s;
	}
	info_press_other(info);
}

int			key_press(int key, t_info *info)
{
	if (key == K_W)
		info->press.k_w = 1;
	if (key == K_S)
		info->press.k_s = 1;
	if (key == K_D)
		info->press.k_d = 1;
	if (key == K_A)
		info->press.k_a = 1;
	if (key == K_AR_R)
		info->press.k_ar_r = 1;
	if (key == K_AR_L)
		info->press.k_ar_l = 1;
	if (key == K_ESC)
		ft_exit(0, 0);
	return (0);
}

int			key_release(int key, t_info *info)
{
	if (key == K_W)
		info->press.k_w = 0;
	if (key == K_S)
		info->press.k_s = 0;
	if (key == K_D)
		info->press.k_d = 0;
	if (key == K_A)
		info->press.k_a = 0;
	if (key == K_AR_R)
		info->press.k_ar_r = 0;
	if (key == K_AR_L)
		info->press.k_ar_l = 0;
	return (0);
}
