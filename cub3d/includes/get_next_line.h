/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 00:42:56 by seungyel          #+#    #+#             */
/*   Updated: 2021/05/24 00:44:19 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define ERROR_NONE 2
# define RES_A_LINE_READ 1
# define RES_REACHED_EOF 0
# define RES_ERROR_HAPPENED -1
# include <stddef.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif
# ifndef OPEN_MAX
#  define OPEN_MAX 4096
# endif

int		get_next_line(int fd, char **line);
char	*ft_strchr(const char *str, int ch);
char	*ft_strnjoin_and_free(char *freeable_str, char *str1, int count_str1);
size_t	ft_strlen(const char *str);
char	*ft_strndup(const char *str, size_t n);
char	*ft_strdup(const char *str);
#endif
