/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 11:55:21 by jae-kim           #+#    #+#             */
/*   Updated: 2021/10/05 11:17:08 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	void	*ptr;
	size_t	i;

	ptr = NULL;
	i = 0;
	while (i < n)
	{
		 *((char *)dst + i) = *((char *)src + i);
		if ((unsigned char)*((char *)src + i) == (unsigned char)c)
		{
			ptr = (void *)dst + i + 1;
			break ;
		}
		i++;
	}
	return (ptr);
}
