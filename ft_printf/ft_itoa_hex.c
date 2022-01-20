/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_hex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 22:09:45 by seungyel          #+#    #+#             */
/*   Updated: 2021/03/21 23:13:52 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
		n = n / 16;
		count++;
	}
	return (count);
}

char		*ft_itoa_hex(long long num, char type)
{
	int			len;
	char		*str;

	len = nbr_len(num);
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
		if (type == 'x')
			str[len - 1] = "0123456789abcdef"[num % 16];
		else
			str[len - 1] = "0123456789ABCDEF"[num % 16];
		num = num / 16;
		if (num == 0)
			break ;
		len--;
	}
	return (str);
}
