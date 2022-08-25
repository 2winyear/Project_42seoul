/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 11:22:52 by mgo               #+#    #+#             */
/*   Updated: 2022/02/15 14:15:35 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>

ssize_t	gnl_read(ssize_t *read_size, int fd, void *buf, size_t count)
{
	*read_size = read(fd, buf, count);
	return (*read_size);
}

size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*gnl_strchr(const char *s, int c)
{
	char	chr_c;

	chr_c = (char)c;
	while (*s != '\0')
	{
		if (*s == chr_c)
			return ((char *)s);
		s++;
	}
	if ((chr_c == '\0') && (*s == '\0'))
		return ((char *)s);
	return (NULL);
}

int	gnl_strndup(char **dest, const char *str, ssize_t len)
{
	char	*duped;
	size_t	i;

	i = 0;
	duped = (char *)malloc(len + 1);
	if (!(duped))
		return (0);
	while (len--)
	{
		duped[i] = str[i];
		i++;
	}
	duped[i] = '\0';
	*dest = duped;
	return (1);
}

char	*gnl_strjoin_with_free(char *s1, char *s2)
{
	char	*joined;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	while (s1[i])
		i++;
	j = 0;
	while (s2[j])
		j++;
	joined = (char *)malloc(i + j + 1);
	if (!(joined))
		return (NULL);
	i = -1;
	while (s1[++i])
		joined[i] = s1[i];
	j = -1;
	while (s2[++j])
		joined[i + j] = s2[j];
	joined[i + j] = '\0';
	free(s1);
	return (joined);
}
