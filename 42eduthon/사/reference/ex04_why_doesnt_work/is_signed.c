#include <limits.h>
#include <stdio.h>

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

static int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	else
		return (0);
}

static int	str_to_num(const char *str, int pn)
{
	size_t	res;
	size_t	res_prev;
	int		i;

	res = 0;
	i = 0;
	while (ft_isdigit(str[i]))
	{
		res_prev = res;
		res = res * 10;
		res = res + (str[i] - '0');
		i++;
		if (res_prev > res)
		{
			if (pn == -1)
				return ((int)LONG_MIN);
			return ((int)LONG_MAX);
		}
	}
	if (res >= (size_t)LONG_MAX + 1 && pn == -1)
		return ((int)LONG_MIN);
	else if (res >= (size_t)LONG_MAX && pn == 1)
		return ((int)LONG_MAX);
	return ((int)((long)res * pn));
}

int	ft_atoi(const char	*str)
{
	size_t	i;
	int		pn;

	i = 0;
	while (ft_isspace(str[i]))
		i++;
	pn = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			pn = -1;
		i++;
	}
	return (str_to_num(&str[i], pn));
}

int	main(int argc, char **argv)
{
	unsigned int	n;

	n = ft_atoi(argv[1]);
	if (argc != 2)
	{
		printf("%s\n", "Give me Number\n");
		return (0);
	}
	printf("%u \n", n);
	return (0);
}
