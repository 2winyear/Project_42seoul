/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <lsy2246@naver.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 16:25:57 by seungyel          #+#    #+#             */
/*   Updated: 2021/01/16 01:11:58 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	count;

	count = 0;
	while (str[count] != '\0')
	{
		count++;
	}
	return (count);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*result;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (!(result = (char*)malloc(sizeof(char) * (len + 1))))
		return (0);
	while (i < len && ft_strlen(s) > start + i)
	{
		result[i] = s[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_strchr(char *str, int c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
		{
			return (&str[i]);
		}
		i++;
	}
	if (c == 0)
		return (&str[i]);
	return (0);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t i;

	if (!dest && !src)
		return (0);
	if (n == 0)
	{
		return (ft_strlen(src));
	}
	i = 0;
	while (src[i] != '\0' && i + 1 < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}
