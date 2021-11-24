/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kim <jae-kim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 11:37:48 by jae-kim           #+#    #+#             */
/*   Updated: 2021/01/06 15:25:09 by jae-kim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*ptr;
	int		i;

	ptr = (char *)s;
	i = 0;
	while (i < (int)n)
	{
		if ((unsigned char)*((char*)s + i) == (unsigned char)c)
			return (ptr);
		else
			ptr++;
		i++;
	}
	return (NULL);
}
