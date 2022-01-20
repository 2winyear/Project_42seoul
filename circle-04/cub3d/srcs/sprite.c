/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 23:48:45 by seungyel          #+#    #+#             */
/*   Updated: 2021/07/04 21:39:32 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		sort_sprites(void)
{
	t_node_sprite	*cur;
	t_node_sprite	*target;
	t_sprite		temp;

	cur = g_model.sprites;
	while (cur != NULL)
	{
		target = cur->next;
		while (target != NULL)
		{
			if (cur->value.dist < target->value.dist)
			{
				temp = target->value;
				target->value = cur->value;
				cur->value = temp;
				target = cur;
			}
			target = target->next;
		}
		cur = cur->next;
	}
}

void		calc_sprite_while(t_calc_sprite *cp, t_node_sprite *r, t_info *info)
{
	cp->sp_x = r->value.pos_x - info->p_x;
	cp->sp_y = r->value.pos_y - info->p_y;
	cp->inv_d = 1.0 / (info->plane_x * info->dir_y - info->dir_x *
	info->plane_y);
	cp->tr_x = cp->inv_d * (info->dir_y * cp->sp_x - info->dir_x * cp->sp_y);
	cp->tr_y = cp->inv_d * (-info->plane_y * cp->sp_x + info->plane_x *
	cp->sp_y);
	cp->sp_s_x = (int)((g_model.width / 2) * (1 + cp->tr_x / cp->tr_y));
	cp->v_m_s = (int)(VMOVE / cp->tr_y);
	cp->sp_h = (int)fabs((g_model.height / cp->tr_y) / VDIV);
	cp->draw_s_y = -cp->sp_h / 2 + g_model.height / 2 + cp->v_m_s;
	if (cp->draw_s_y < 0)
		cp->draw_s_y = 0;
	cp->draw_e_y = cp->sp_h / 2 + g_model.height / 2 + cp->v_m_s;
	if (cp->draw_e_y >= g_model.height)
		cp->draw_e_y = g_model.height - 1;
	cp->sp_w = (int)fabs((g_model.height / cp->tr_y) / UDIV);
	cp->draw_s_x = -cp->sp_w / 2 + cp->sp_s_x;
	if (cp->draw_s_x < 0)
		cp->draw_s_x = 0;
	cp->draw_e_x = cp->sp_w / 2 + cp->sp_s_x;
	if (cp->draw_e_x >= g_model.width)
		cp->draw_e_x = g_model.width - 1;
	cp->st = cp->draw_s_x;
}

void		calc_sprite_while_while(t_calc_sprite *cp, t_info *info)
{
	cp->d = (cp->y - cp->v_m_s) * 256 - g_model.height * 128
					+ cp->sp_h * 128;
	cp->tex_y = ((cp->d * GUMBA_HEIGHT) / cp->sp_h) / 256;
	cp->idx = GUMBA_WIDTH * cp->tex_y + cp->tex_x;
	if (cp->idx >= 0 && cp->idx < GUMBA_HEIGHT * GUMBA_WIDTH)
	{
		cp->color = g_gumba_texture[cp->idx];
		if ((cp->color & 0x00FFFFFF) != 0)
			info->data1[cp->y * g_model.width + cp->st] = cp->color;
	}
	cp->y++;
}

void		calc_sprite(t_info *info)
{
	t_calc_sprite cp;
	t_node_sprite *cur;

	calc_dist(info);
	sort_sprites();
	cur = g_model.sprites;
	while (cur != NULL)
	{
		calc_sprite_while(&cp, cur, info);
		while (cp.st < cp.draw_e_x)
		{
			cp.tex_x = (int)((256 * (cp.st - (-cp.sp_w / 2 + cp.sp_s_x)) *
			GUMBA_WIDTH / cp.sp_w) / 256);
			if (cp.tr_y > 0 && cp.st > 0 && cp.st < g_model.width
			&& cp.tr_y < info->z_buf[cp.st])
			{
				cp.y = cp.draw_s_y;
				while (cp.y < cp.draw_e_y)
					calc_sprite_while_while(&cp, info);
			}
			cp.st++;
		}
		cur = cur->next;
	}
}

void		input_node_sprite(int i, int j)
{
	t_node_sprite *new_node;
	t_node_sprite *cur;

	cur = g_model.sprites;
	new_node = malloc(sizeof(t_node_sprite));
	if (new_node == NULL)
		ft_exit(0, 1);
	new_node->value.pos_x = j + 0.5;
	new_node->value.pos_y = i + 0.5;
	new_node->value.texture_id = TEX_GHOST;
	new_node->value.dist = 0;
	new_node->next = NULL;
	g_model.real_map[j][i] = 0;
	if (g_model.sprites == NULL)
	{
		g_model.sprites = new_node;
		return ;
	}
	while (cur->next != NULL)
		cur = cur->next;
	cur->next = new_node;
}
