/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 21:44:29 by chanhpar          #+#    #+#             */
/*   Updated: 2022/08/24 21:45:02 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <regex.h>
#include <unistd.h>

void	eleven_number_checker(const char *str)
{
	regex_t		preg;
	regmatch_t	pmatch[1];
	char		*pattern;
	int			len;

	if (!str)
		return ;
	pattern = "[0-9]{11}";
	regcomp(&preg, pattern, REG_EXTENDED);
	if (!regexec(&preg, str, 1, pmatch, 0))
	{
		len = pmatch[0].rm_eo - pmatch[0].rm_so;
		write(1, str + pmatch[0].rm_so, len);
		write(1, "\n", 1);
	}
	else
		write(1, "KO\n", 3);
	regfree(&preg);
}
