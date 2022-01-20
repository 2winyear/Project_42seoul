/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 02:59:27 by seungyel          #+#    #+#             */
/*   Updated: 2021/05/23 03:36:29 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

char		*ft_strchr(const char *str1, int ch)
{
	unsigned char	symbol;
	char			*cur_str;

	cur_str = (char *)str1;
	symbol = ch;
	while (1)
	{
		if (*cur_str == symbol)
			return (cur_str);
		if (*cur_str == '\0')
			return (NULL);
		++cur_str;
	}
}

char		*ft_strnjoin_and_free(char *freeable_str,
									char *str1, int count_str1)
{
	char	*new_str;
	char	*cur_free_str;
	size_t	idx;
	size_t	len_newstr;

	idx = 0;
	cur_free_str = freeable_str;
	len_newstr = cur_free_str != NULL ?
				ft_strlen(cur_free_str) + ft_strlen(str1) : ft_strlen(str1);
	if ((new_str = malloc((len_newstr + 1) * sizeof(char))) == NULL)
		return (NULL);
	if (cur_free_str != NULL)
	{
		while (*cur_free_str != '\0')
			new_str[idx++] = *cur_free_str++;
	}
	while (*str1 != '\0' && count_str1-- > 0)
		new_str[idx++] = *str1++;
	new_str[idx] = '\0';
	free(freeable_str);
	return (new_str);
}

size_t		ft_strlen(const char *str1)
{
	const char *cur_str;

	cur_str = str1;
	while (*cur_str != '\0')
	{
		++cur_str;
	}
	return (cur_str - str1);
}

char		*ft_strndup(const char *str, size_t n)
{
	const char	*cur_src;
	const char	*end_src;
	char		*cur_dst;
	void		*new_str;
	size_t		len;

	len = ft_strlen(str);
	len = len > n ? n : len;
	if ((new_str = malloc(sizeof(char) * len + 1)) == NULL)
		return (NULL);
	cur_dst = new_str;
	cur_src = str;
	end_src = cur_src + len;
	while (cur_src != end_src)
	{
		*cur_dst = *cur_src;
		++cur_src;
		++cur_dst;
	}
	*cur_dst = '\0';
	return (new_str);
}

char		*ft_strdup(const char *str)
{
	const char	*cur_src;
	const char	*end_src;
	char		*cur_dst;
	void		*new_str;
	size_t		len;

	len = ft_strlen(str);
	if ((new_str = malloc(sizeof(char) * len + 1)) == NULL)
		return (NULL);
	cur_dst = new_str;
	cur_src = str;
	end_src = cur_src + len;
	while (cur_src != end_src)
	{
		*cur_dst = *cur_src;
		++cur_src;
		++cur_dst;
	}
	*cur_dst = '\0';
	return (new_str);
}
