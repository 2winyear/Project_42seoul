/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 11:15:09 by mgo               #+#    #+#             */
/*   Updated: 2022/02/15 13:55:51 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_gnl	*new_storage(int fd)
{
	t_gnl	*ret;

	ret = malloc(sizeof(t_gnl));
	if (!ret)
		return (NULL);
	ret->fd = fd;
	ret->content = 0;
	ret->next = 0;
	return (ret);
}

static int	set_carrier(t_gnl **storage, t_gnl **to_set, int fd)
{
	t_gnl	*carrier;
	t_gnl	*tmp;

	if (!(*storage))
	{
		*storage = new_storage(fd);
		if (!(*storage))
			return (0);
	}
	carrier = *storage;
	while (carrier && (fd != carrier->fd))
	{
		tmp = carrier;
		carrier = carrier->next;
	}
	if (!carrier)
	{
		carrier = new_storage(fd);
		if (!(carrier))
			return (0);
		tmp->next = carrier;
	}
	*to_set = carrier;
	return (1);
}

static int	del_storage(t_gnl **storage, int fd)
{
	t_gnl	*prev;
	t_gnl	*tmp;

	prev = 0;
	tmp = *storage;
	if (tmp == 0)
		return (-1);
	while ((tmp->next) && (tmp->fd != fd))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (!prev)
		*storage = tmp->next;
	else if (prev)
		prev->next = tmp->next;
	if (fd == tmp->fd)
	{
		free(tmp->content);
		free(tmp);
	}
	return (-1);
}

static int	set_line(char **line, t_gnl **storage, t_gnl *carrier)
{
	char	*newl;
	char	*tmp_content;

	newl = gnl_strchr(carrier->content, '\n');
	if (newl)
	{
		if (!gnl_strndup(line, carrier->content, (newl - carrier->content)))
			return (del_storage(storage, carrier->fd));
		tmp_content = carrier->content;
		if (!gnl_strndup(&(carrier->content), newl + 1, gnl_strlen(newl + 1)))
		{
			free(tmp_content);
			return (del_storage(storage, carrier->fd));
		}
		free(tmp_content);
		return (1);
	}
	if (!gnl_strndup(line, carrier->content, gnl_strlen(carrier->content)))
		return (del_storage(storage, carrier->fd));
	del_storage(storage, carrier->fd);
	return (0);
}

int	get_next_line(int fd, char **line)
{
	static t_gnl	*storage;
	t_gnl			*carrier;
	char			buf[BUFFER_SIZE + 1];
	ssize_t			read_size;

	if ((fd < 0) || !line || (BUFFER_SIZE <= 0))
		return (-1);
	if (!set_carrier(&storage, &carrier, fd))
		return (del_storage(&storage, fd));
	while (gnl_read(&read_size, fd, buf, BUFFER_SIZE) >= 0)
	{
		buf[read_size] = '\0';
		if (carrier->content)
			carrier->content = gnl_strjoin_with_free(carrier->content, buf);
		else
			gnl_strndup(&(carrier->content), buf, read_size);
		if (!(carrier->content))
			return (del_storage(&storage, fd));
		if (gnl_strchr(carrier->content, '\n') || read_size == 0)
			break ;
	}
	if (read_size < 0)
		return (del_storage(&storage, fd));
	return (set_line(line, &storage, carrier));
}
