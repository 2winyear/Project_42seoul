#include "push_swap.h"
#include <stdio.h>
#include <stdlib.h>

int	ft_atoi(const char *str)
{
	long long	sum;
	int			sign;
	int			count;
	sum = 0;
	count = 0;
	sign = 1;
	while (*str == '\t' || *str == '\n' || *str == '\v' \
			|| *str == '\f' || *str == '\r' || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = (-1) * sign;
	while (*str >= 48 && *str <= 57)
	{
		sum = sum * 10 + *str++ - 48;
		count++;
	}
	sum *= sign;
	if (sign == 1 && count > 20)
		return (-1);
	if (sign == -1 && count > 20)
		return (0);
	return (sum);
}

static size_t	count_digit(int n)
{
	size_t	ret;

	if (n == 0)
		return (1);
	ret = 1;
	while (n >= 10 || n <= (-10))
	{
		n = n / 10;
		ret++;
	}
	return (ret);
}

static char		*allocate_digit(char *ret, int n, size_t count, char sign)
{
	if (n == 0)
		*ret = 48;
	*(ret + count) = '\0';
	if (sign)
	{
		*ret = '-';
		*(ret + --count) = n % 10 * (-1) + 48;
		n = n / 10 * (-1);
	}
	while (n >= 10)
	{
		*(ret + count - 1) = (n % 10) + 48;
		n = n / 10;
		count--;
	}
	if (n != 0)
		*(ret + count - 1) = n + 48;
	return (ret);
}

char			*ft_itoa(int n)
{
	size_t		count;
	char		sign;
	char		*ret;

	sign = '\0';
	count = count_digit(n);
	if (n < 0)
	{
		sign = '-';
		count++;
	}
	if (!(ret = malloc(sizeof(char) * (count + 1))))
		return (NULL);
	ret = allocate_digit(ret, n, count, sign);
	return (ret);
}