/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 04:54:18 by seungyel          #+#    #+#             */
/*   Updated: 2020/10/12 02:23:46 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
