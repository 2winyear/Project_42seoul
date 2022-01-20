/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 02:59:35 by seungyel          #+#    #+#             */
/*   Updated: 2021/05/23 03:33:17 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

static int		read_fd(int fd, int *len_read,
						char **buf_saved_str, char *buf_read)
{
	while ((*len_read = read(fd, buf_read, BUFFER_SIZE)) > 0)
	{
		buf_read[*len_read] = '\0';
		if (ft_strchr(buf_read, '\n') != NULL)
			return (ERROR_NONE);
		if ((*buf_saved_str =
			ft_strnjoin_and_free(*buf_saved_str, buf_read, *len_read)) == NULL)
			return (RES_ERROR_HAPPENED);
	}
	if (*len_read < 0)
		return (RES_ERROR_HAPPENED);
	return (ERROR_NONE);
}

static int		handle_saved_str(char **buf_saved_str, char **line)
{
	char	*pos_newline;
	char	*temp;
	int		idx_newline;

	if (*buf_saved_str != NULL &&
		(pos_newline = ft_strchr(*buf_saved_str, '\n')) != NULL)
	{
		idx_newline = ft_strlen(*buf_saved_str) - ft_strlen(pos_newline);
		if ((*line = ft_strndup(*buf_saved_str, idx_newline)) == NULL)
			return (RES_ERROR_HAPPENED);
		if ((temp = ft_strdup(pos_newline + 1)) == NULL)
			return (RES_ERROR_HAPPENED);
		free(*buf_saved_str);
		*buf_saved_str = temp;
		return (RES_A_LINE_READ);
	}
	return (ERROR_NONE);
}

static int		seperate_str(int len_read, char **line,
							char **buf_saved_str, char *buf_read)
{
	char	*pos_newline;

	if (len_read != 0)
	{
		pos_newline = ft_strchr(buf_read, '\n');
		if ((*line = ft_strnjoin_and_free(*buf_saved_str, buf_read,
			len_read - ft_strlen(pos_newline))) == NULL)
			return (RES_ERROR_HAPPENED);
		if ((*buf_saved_str = ft_strdup(pos_newline + 1)) == NULL)
			return (RES_ERROR_HAPPENED);
	}
	else
	{
		if ((*line = ft_strnjoin_and_free(*buf_saved_str, "", 0)) == NULL)
			return (RES_ERROR_HAPPENED);
		*buf_saved_str = NULL;
	}
	return (len_read > 0 ? RES_A_LINE_READ : RES_REACHED_EOF);
}

static int		handle_read_and_seperate(int fd, char **line,
									char **buf_saved_str, char **buf_read)
{
	int		len_read;
	int		result;

	if ((*buf_read = malloc(sizeof(char) * (BUFFER_SIZE + 1))) == NULL)
		return (RES_ERROR_HAPPENED);
	*buf_read[0] = '\0';
	result = read_fd(fd, &len_read, buf_saved_str, *buf_read);
	if (result == ERROR_NONE)
		result = seperate_str(len_read, line, buf_saved_str, *buf_read);
	return (result);
}

int				get_next_line(int fd, char **line)
{
	static char		*buf_saved_str;
	char			*buf_read;
	int				result;

	buf_read = NULL;
	if (BUFFER_SIZE <= 0 || line == NULL || fd < 0 || fd > OPEN_MAX)
		return (RES_ERROR_HAPPENED);
	result = handle_saved_str(&buf_saved_str, line);
	if (result == ERROR_NONE)
		result = handle_read_and_seperate(fd, line, &buf_saved_str, &buf_read);
	free(buf_read);
	return (result);
}
