/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jeongble <jeongble@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 21:34:05 by jeongble          #+#    #+#             */
/*   Updated: 2022/08/24 11:19:09 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*buf_join(char **str, char *buffer, t_info *info)
{
	char	*new_str;
	int		i;

	if (info->index == (size_t)info->rbyte && !info->old_len && !info->new_len)
		return (0);
	new_str = malloc(info->old_len + info->new_len + 1);
	if (*(str))
	{
		i = -1;
		while (++i < (int)info->old_len)
			*(new_str + i) = *(*(str) + i);
		free(*(str));
	}
	i = -1;
	while (++ i < (int)info->new_len)
		*(new_str + info->old_len + i) = *(buffer + i);
	*(new_str + info->old_len + info->new_len) = 0;
	info->old_len += info->new_len;
	info->new_len = 0;
	*(str) = new_str;
	return (*(str));
}

char	*get_next_line(int fd)
{
	static t_info	info;
	char			*str;

	if (fd < 0 || read(fd, info.buf, 0) == -1)
		return (0);
	str = 0;
	info.old_len = 0;
	info.new_len = 0;
	while (1)
	{
		if (info.index == (size_t)info.rbyte)
		{
			buf_join(&str, info.buf + info.rbyte - (info.new_len), &info);
			info.rbyte = read(fd, info.buf, BUFFER_SIZE);
			info.index = 0;
			if (!(info.rbyte))
				return (str);
		}
		if (info.buf[info.index] == '\n')
			return (buf_join(
					&str, info.buf + info.index++ - info.new_len++, &info));
		info.index ++;
		info.new_len ++;
	}
}
