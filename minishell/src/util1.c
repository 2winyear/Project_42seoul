/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeukim <byeukim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:16:01 by byeukim           #+#    #+#             */
/*   Updated: 2021/12/02 12:16:02 by byeukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_strcmp(char *str1, char *str2)
{
	int	idx;

	idx = 0;
	while (str1[idx] && str2[idx])
	{
		if (str1[idx] != str2[idx])
			return (str1[idx] - str2[idx]);
		idx++;
	}
	if (str1[idx] || str2[idx])
		return (str1[idx] - str2[idx]);
	return (0);
}

int	ft_strncmp(char *str1, char *str2, int n)
{
	int	idx;

	idx = -1;
	while (++idx < n && str1[idx] && str2[idx])
	{
		if (str1[idx] != str2[idx])
			return (str1[idx] - str2[idx]);
	}
	if (idx == n)
		return (0);
	else
		return (str1[idx] - str2[idx]);
}

char	*ft_strncpy(char *line, int n)
{
	char	*str;
	int		i;

	str = malloc(sizeof(char) * n);
	i = -1;
	while (++i < n)
		str[i] = line[i];
	str[i] = '\0';
	return (str);
}

char	*ft_strnstr(const char *b, const char *l, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (*l == 0)
		return ((char *)b);
	while (i < len && b[i])
	{
		j = 0;
		while (*(b + i + j) == *(l + j) && i + j < len)
		{
			if (l[j + 1] == '\0')
				return ((char *)(b + i));
			j++;
		}
		i++;
	}
	return (0);
}

char	*ft_strdup(char *s1)
{
	size_t	i;
	char	*cpy;

	i = 0;
	if (!s1)
		return (NULL);
	cpy = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!cpy)
		return (NULL);
	while (s1[i] != '\0')
	{
		cpy[i] = s1[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}
