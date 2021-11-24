/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 06:29:19 by seungyel          #+#    #+#             */
/*   Updated: 2020/10/14 18:31:53 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char		*new_dest;
	const unsigned char	*new_src;
	unsigned char		find;
	size_t				i;

	i = 0;
	find = c;
	new_dest = dest;
	new_src = src;
	while (i < n)
	{
		new_dest[i] = new_src[i];
		if (new_src[i] == find)
			return (new_dest + (i + 1));
		i++;
	}
	return (0);
}
