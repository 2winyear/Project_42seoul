/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 02:59:01 by seungyel          #+#    #+#             */
/*   Updated: 2021/07/04 19:56:54 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_isalpha(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	return (0);
}

int		ft_strcmp(char *dst, char *src)
{
	while (*dst != '\0' && *dst == *src)
	{
		dst++;
		src++;
	}
	return (*dst - *src);
}

int		ft_isupper(char symbol)
{
	return ('A' <= symbol && symbol <= 'Z');
}

int		ft_isspace(char symbol)
{
	if (symbol == ' ')
		return (1);
	else
		return (0);
}

void	ft_exit(int no, int error)
{
	free_sprite();
	free_node();
	free_map();
	if (g_model.info.mlx != NULL && g_model.info.img1 != NULL &&
		g_model.info.win != NULL && g_model.info.img2 != NULL)
	{
		mlx_destroy_image(g_model.info.mlx, g_model.info.img1);
		mlx_destroy_image(g_model.info.mlx, g_model.info.img2);
		mlx_destroy_window(g_model.info.mlx, g_model.info.win);
	}
	if (error)
		printf(ERROR_MSG);
	exit(no);
}
