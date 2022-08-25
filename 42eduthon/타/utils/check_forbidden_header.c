/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_forbidden_header.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 12:10:59 by chanhpar          #+#    #+#             */
/*   Updated: 2022/08/25 01:06:41 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include "get_next_line.h"

static int	ft_regex(const char *pattern, char *input, regmatch_t *pmatch)
{
	regex_t	reg;
	int		ret;

	ret = regcomp(&reg, pattern, REG_EXTENDED);
	if (ret != 0)
		return (-1);
	ret = regexec(&reg, input, 2, pmatch, 0);
	regfree(&reg);
	if (ret != 0)
		return (-1);
	else
		return (0);
}

static int	find_forbidden_header(char *filename, char *line)
{
	const char	*pattern;
	char		buffer[128];
	size_t		len;
	regmatch_t	pmatch[2];

	pattern = "#[ ]*include[ ]*<([a-z]+[/]?[a-z]+)\\.h>";
	if (ft_regex(pattern, line, pmatch) == 0)
	{
		len = pmatch[1].rm_eo - pmatch[1].rm_so;
		memcpy(buffer, line + pmatch[1].rm_so, len);
		buffer[len] = '\0';
		if (strcmp("unistd", buffer) != 0)
		{
			if (strstr(filename, "eleven_number_checker.c") != 0 \
					|| strcmp("regex", buffer) != 0)
				return (1);
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		forbiden_header_flag;

	if (argc != 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (1);
	forbiden_header_flag = 0;
	while (forbiden_header_flag == 0)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		forbiden_header_flag = find_forbidden_header(argv[1], line);
		free(line);
	}
	close(fd);
	return (forbiden_header_flag);
}
