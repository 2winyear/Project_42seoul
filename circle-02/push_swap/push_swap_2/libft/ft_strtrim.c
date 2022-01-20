/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kim <jae-kim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 12:48:41 by jae-kim           #+#    #+#             */
/*   Updated: 2021/01/08 11:26:37 by jae-kim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int				check_trim(char a, char const *set)
{
	int			i;

	i = 0;
	while (*(set + i))
	{
		if (a == *(set + i))
			return (1);
		i++;
	}
	return (0);
}

char					*ft_strtrim(char const *s1, char const *set)
{
	char		*ptr;
	size_t		len_s1;
	size_t		front;
	size_t		end;

	front = 0;
	end = 0;
	if (s1 == NULL)
		return (NULL);
	len_s1 = ft_strlen(s1);
	while (front < len_s1 && check_trim(*(s1 + front), set))
		front += check_trim(*(s1 + front), set);
	if (front == len_s1)
		return (ft_strdup(""));
	while (check_trim(*(s1 + len_s1 - 1 - end), set))
		end += check_trim(*(s1 + len_s1 - 1 - end), set);
	ptr = malloc(sizeof(char) * (len_s1 - front - end + 1));
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, s1 + front, len_s1 - front - end + 1);
	return (ptr);
}
