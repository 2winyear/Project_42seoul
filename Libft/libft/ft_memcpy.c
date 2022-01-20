/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 21:49:32 by seungyel          #+#    #+#             */
/*   Updated: 2020/12/01 11:24:05 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t num)
{
	size_t					i;
	unsigned char			*new_dest;
	const unsigned	char	*new_src;

	i = 0;
	new_dest = dest;
	new_src = src;
	if (!dest && !src)
		return (NULL);
	while (i < num)
	{
		new_dest[i] = new_src[i];
		i++;
	}
	return (new_dest);
}
