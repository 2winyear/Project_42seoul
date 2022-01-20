/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 22:09:45 by seungyel          #+#    #+#             */
/*   Updated: 2020/12/02 13:45:48 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	nbr_len(long long n)
{
	int	count;

	if (n == 0)
		return (1);
	count = 0;
	if (n < 0)
	{
		n = n * (-1);
		count++;
	}
	while (n != 0)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char		*ft_itoa(int n)
{
	int			len;
	char		*str;
	long long	num;

	num = n;
	len = nbr_len((long long)n);
	if (!(str = (char*)malloc(sizeof(char) * (1 + len))))
		return (NULL);
	if (num < 0)
	{
		*str = '-';
		num = num * -1;
	}
	str[len] = 0;
	while (1)
	{
		str[len - 1] = (num % 10) + '0';
		num = num / 10;
		if (num == 0)
			break ;
		len--;
	}
	return (str);
}
