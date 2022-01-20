/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 00:56:31 by jae-kim           #+#    #+#             */
/*   Updated: 2021/10/05 11:42:25 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*((char *)s1 + i) != *((char *)s2 + i))
			return ((unsigned char)*((char *)s1 + i) \
					- (unsigned char)*((char *)s2 + i));
		i++;
	}
	return (0);
}
