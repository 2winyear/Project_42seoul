/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgo <mgo@student.42seoul.kr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/01 11:18:05 by mgo               #+#    #+#             */
/*   Updated: 2022/02/01 12:38:52 by mgo              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

typedef struct s_gnl
{
	int		fd;
	char	*content;
	void	*next;
}				t_gnl;

// get_next_line.c
int				get_next_line(int fd, char **line);

// get_next_line_utils.c
char			*gnl_strjoin_with_free(char *s1, char *s2);
int				gnl_strndup(char **dest, const char *str, ssize_t len);
char			*gnl_strchr(const char *s, int c);
size_t			gnl_strlen(const char *s);
ssize_t			gnl_read(ssize_t *read_size, int fd, void *buf, size_t count);

#endif
