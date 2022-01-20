/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <lsy2246@naver.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 21:09:03 by seungyel          #+#    #+#             */
/*   Updated: 2020/11/20 16:28:00 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char *arr;

	if (!(arr = (char*)malloc(sizeof(char) * count * size)))
		return (0);
	ft_bzero(arr, size * count);
	return (arr);
}
