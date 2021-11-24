/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 13:39:40 by seungyel          #+#    #+#             */
/*   Updated: 2020/10/12 13:39:45 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str1, const char *str2, size_t num)
{
	size_t			i;
	unsigned char	*new_str1;
	unsigned char	*new_str2;

	new_str1 = (unsigned char *)str1;
	new_str2 = (unsigned char *)str2;
	i = 0;
	while (i < num && (new_str1[i] != '\0' || new_str2[i] != '\0'))
	{
		if (new_str1[i] != new_str2[i])
			return (new_str1[i] - new_str2[i]);
		i++;
	}
	return (0);
}
