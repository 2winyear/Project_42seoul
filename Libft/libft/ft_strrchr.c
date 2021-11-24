/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <lsy2246@naver.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 20:20:31 by seungyel          #+#    #+#             */
/*   Updated: 2020/10/21 21:51:54 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *str, int c)
{
	int count;

	count = ft_strlen(str);
	while (count >= 0)
	{
		if (str[count] == c)
			return (&str[count]);
		count--;
	}
	return (0);
}
