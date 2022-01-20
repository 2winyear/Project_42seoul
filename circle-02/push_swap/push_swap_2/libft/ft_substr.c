/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kim <jae-kim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 11:39:13 by jae-kim           #+#    #+#             */
/*   Updated: 2021/01/06 15:07:06 by jae-kim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ret;
	unsigned int	count;
	int				i;

	count = 0;
	i = 0;
	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (start + len > ft_strlen(s))
		len = ft_strlen(s) - start;
	if (!(ret = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (*(s + count))
	{
		if (count == start)
		{
			ft_strlcpy(ret, s + count, len + 1);
			break ;
		}
		count++;
	}
	return (ret);
}
