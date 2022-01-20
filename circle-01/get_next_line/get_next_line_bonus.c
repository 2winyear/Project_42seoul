/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <lsy2246@naver.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 16:24:42 by seungyel          #+#    #+#             */
/*   Updated: 2021/01/16 01:10:43 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strdup(char *s)
{
	char *arr;

	if (!(arr = (char *)malloc(ft_strlen(s) + 1)))
		return (NULL);
	ft_strlcpy(arr, s, ft_strlen(s) + 1);
	return (arr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (0);
	s = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s)
		return (0);
	while (s1[i] != '\0')
	{
		s[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		s[i] = s2[j];
		i++;
		j++;
	}
	s[i] = '\0';
	return (s);
}

int		ft_min(int ret)
{
	return (ret < 1 ? ret : 1);
}

void	ft_half(char **backup, char **line)
{
	char	*backbackup;
	char	*tmp;

	if ((tmp = ft_strchr(*backup, '\n')) != NULL)
	{
		*tmp = '\0';
		*line = ft_strdup(*backup);
		backbackup = *backup;
		*backup = ft_strdup(tmp + 1);
		free(backbackup);
	}
	else
	{
		*line = *backup;
		*backup = NULL;
	}
}

int		get_next_line(int fd, char **line)
{
	int			ret;
	char		*backbackup;
	static char	*backup[OPEN_MAX];
	char		buf[BUFFER_SIZE + 1];

	ret = 1;
	if (BUFFER_SIZE <= 0 || fd < 0 || !line)
		return (-1);
	*line = NULL;
	if (backup[fd] == NULL)
		backup[fd] = ft_strdup("");
	while (ft_strchr(backup[fd], '\n') == NULL &&
			(ret = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[ret] = '\0';
		backbackup = backup[fd];
		backup[fd] = ft_strjoin(backbackup, buf);
		free(backbackup);
	}
	if (ret < 0)
		return (-1);
	ft_half(&backup[fd], line);
	return (ft_min(ret));
}
