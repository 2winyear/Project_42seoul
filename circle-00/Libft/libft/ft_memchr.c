/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 06:31:00 by seungyel          #+#    #+#             */
/*   Updated: 2020/12/01 13:55:12 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *ptr, int value, size_t n)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	v;

	p = (unsigned char *)ptr;
	v = (unsigned char)value;
	i = 0;
	while (i < n)
	{
		if (p[i] == v)
			return (void *)(p + i);
		i++;
	}
	return (NULL);
}
