/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeukim <byeukim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:16:04 by byeukim           #+#    #+#             */
/*   Updated: 2021/12/02 12:16:07 by byeukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strndup(char *s1, int len)
{
	int		idx;
	char	*s2;

	idx = -1;
	s2 = malloc(len + 1);
	if (!s2)
		return (NULL);
	while (++idx < len)
		s2[idx] = s1[idx];
	s2[idx] = '\0';
	return (s2);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	size_t	len;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	str = (char *)s1;
	len = ft_strlen(s1) + ft_strlen(s2);
	i = -1;
	j = -1;
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	while (s1[++i] != 0)
		str[i] = s1[i];
	while (s2[++j] != 0)
		str[i++] = s2[j];
	str[i] = 0;
	return (str);
}

char	*ft_strjointri(char *str1, char *str2, char *str3)
{
	char	*str;
	int		len;
	int		i;
	int		j;
	int		k;

	len = ft_strlen(str1) + ft_strlen(str2) + ft_strlen(str3);
	str = (malloc(sizeof(char) * len + 1));
	if (!str)
		return (NULL);
	i = -1;
	j = -1;
	k = -1;
	while (str1[++i])
		str[i] = str1[i];
	while (str2[++j])
		str[i++] = str2[j];
	while (str3[++k])
		str[i++] = str3[k];
	str[i] = '\0';
	return (str);
}
