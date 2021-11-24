/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 11:37:48 by jae-kim           #+#    #+#             */
/*   Updated: 2021/10/05 11:17:38 by seungyel         ###   ########.fr       */
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
		if ((unsigned char)*((char *)s + i) == (unsigned char)c)
			return (ptr);
		else
			ptr++;
		i++;
	}
	return (NULL);
}
