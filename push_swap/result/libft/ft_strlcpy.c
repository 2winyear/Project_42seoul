/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 13:15:15 by jae-kim           #+#    #+#             */
/*   Updated: 2021/10/05 11:24:49 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t		len;

	len = 0;
	if (src == NULL)
		return (0);
	while ((len < dstsize - 1) && *src && (dstsize != 0))
	{
		*dst = *src;
		src++;
		dst++;
		len++;
	}
	if (dstsize != 0)
		*dst = '\0';
	while (*(src++))
		len++;
	return (len);
}
