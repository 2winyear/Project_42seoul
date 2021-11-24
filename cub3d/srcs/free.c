/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 03:40:21 by seungyel          #+#    #+#             */
/*   Updated: 2021/05/24 04:22:01 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_map(void)
{
	if (g_model.real_map != NULL)
		free(g_model.real_map[0]);
	free(g_model.real_map);
}

void	free_sprite(void)
{
	t_node_sprite *cur;
	t_node_sprite *temp;

	cur = g_model.sprites;
	while (cur != NULL)
	{
		temp = cur;
		cur = cur->next;
		free(temp);
	}
}

void	free_node(void)
{
	t_node *cur;
	t_node *prev;

	cur = g_model.map;
	while (cur != NULL)
	{
		prev = cur;
		cur = cur->next;
		free(prev->value);
		free(prev);
	}
}
