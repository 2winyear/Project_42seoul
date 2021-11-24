/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/10 06:35:26 by seungyel          #+#    #+#             */
/*   Updated: 2020/12/02 11:46:26 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *b, const char *l, size_t len)
{
	size_t i;
	size_t j;

	i = 0;
	if (*l == 0)
		return ((char*)b);
	while (i < len && b[i])
	{
		j = 0;
		while (*(b + i + j) == *(l + j) && i + j < len)
		{
			if (l[j + 1] == '\0')
				return (char*)(b + i);
			j++;
		}
		i++;
	}
	return (0);
}
