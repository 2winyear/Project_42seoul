/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 18:28:14 by seungyel          #+#    #+#             */
/*   Updated: 2020/12/01 11:55:58 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *s)
{
	char *arr;

	if (!(arr = (char *)malloc(ft_strlen(s) + 1)))
		return (NULL);
	ft_strlcpy(arr, s, ft_strlen(s) + 1);
	return (arr);
}
