/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mem.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 06:33:04 by seungyel          #+#    #+#             */
/*   Updated: 2021/05/24 03:58:46 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_memmove(void *dest, void *src, size_t n)
{
	char *tmp;
	char *s;

	if (!dest && !src)
		return (NULL);
	if (dest <= src)
	{
		tmp = dest;
		s = src;
		while (n--)
			*tmp++ = *s++;
	}
	else
	{
		tmp = dest;
		tmp += n;
		s = src;
		s += n;
		while (n--)
			*--tmp = *--s;
	}
	return (dest);
}

void	*ft_memset(void *ptr, int value, size_t num)
{
	unsigned char	*new_dest;
	unsigned char	src;
	size_t			i;

	new_dest = ptr;
	src = value;
	i = 0;
	while (i < num)
	{
		*new_dest++ = src;
		i++;
	}
	return (ptr);
}

int		ft_memexit(void)
{
	ft_exit(0, 0);
	return (0);
}
