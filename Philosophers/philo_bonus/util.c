/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 10:54:04 by seungyel          #+#    #+#             */
/*   Updated: 2021/12/13 15:07:05 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosopher_bonus.h"

int	ft_isspace(char c)
{
	if (c == '\n' || c == '\t' || c == '\v'
		|| c == '\r' || c == '\f' || c == ' ')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	value;

	i = 0;
	value = 0;
	sign = 1;
	while ((str[i] != '\0') && (ft_isspace(str[i]) == 1))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		value = value * 10 + (str[i] - '0');
		i++;
	}
	return (sign * value);
}

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

char	*ft_itoa(int n)
{
	int			len;
	char		*str;
	long long	num;

	num = n;
	len = nbr_len((long long)n);
	str = (char *)malloc(sizeof(char) * (1 + len));
	if (!str)
		return (NULL);
	if (num < 0)
	{
		*str = '-';
		num = num * -1;
	}
	str[len] = 0;
	while (true)
	{
		str[len - 1] = (num % 10) + '0';
		num = num / 10;
		if (num == 0)
			break ;
		len--;
	}
	return (str);
}
