/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 12:45:19 by jae-kim           #+#    #+#             */
/*   Updated: 2021/10/05 12:59:53 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*erase_deli(char *ptr, char c)
{
	if (!*ptr)
		return (NULL);
	while (*ptr == c)
		ptr++;
	return (ptr);
}

static size_t	get_count(char const *s, char c)
{
	size_t	ret;
	char	*ptr;

	ret = 0;
	if (*s == '\0')
		return (0);
	if (c == 0)
		return (1);
	ptr = (char *)s;
	ptr = erase_deli(ptr, c);
	while (*ptr)
	{
		ret++;
		ptr = ft_strchr(ptr, c);
		if (!ptr)
			return (ret);
		ptr = erase_deli(ptr, c);
	}
	return (ret);
}

char	*allocate_part_2(char *ptr, char *ptr_forward, char const *s)
{
	char	*part;

	if (!ptr_forward)
		part = ft_strdup(ptr);
	else
		part = ft_substr(s, ptr - s, ptr_forward - ptr);
	return (part);
}

static void	allocate_part(char **ret, char const *s, char c, size_t count)
{
	char		*ptr_forward;
	char		*ptr;
	char		*part;
	size_t		i;

	i = 0;
	ptr = (char *)s;
	while (i < count)
	{
		ptr = erase_deli(ptr, c);
		ptr_forward = ft_strchr(ptr, c);
		part = allocate_part_2(ptr, ptr_forward, s);
		if (part == NULL)
		{
			while (i)
				free(ret[--i]);
			ret = NULL;
			free(ret);
		}
		ret[i++] = part;
		ptr = ptr_forward;
	}
	ret[i] = 0;
}

char	**ft_split(char const *s, char c)
{
	size_t		count;
	char		**ret;

	if (s == NULL)
		return (NULL);
	count = get_count(s, c);
	ret = (char **)malloc(sizeof(char *) * (count + 1));
	if (!ret)
		return (NULL);
	ret[count] = 0;
	if (count == 0)
		return (ret);
	allocate_part(ret, s, c, count);
	return (ret);
}
