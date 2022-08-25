#include "ex00.h"

static size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(src);
	i = 0;
	if (dstsize == 0)
		return (len);
	while (i + 1 < dstsize && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (len);
}

static size_t	get_strs_size(char const *s, char c)
{
	size_t		size;
	int			flag;

	size = 1;
	flag = 0;
	while (*s)
	{
		if (*s != c)
			break ;
		s++;
	}
	while (*s)
	{
		if (*s == c)
		{
			if (*(s + 1) != c && *(s + 1) != 0)
				size++;
		}
		s++;
	}
	return (size);
}

static void		set_all_memory_null(char **strs, size_t index)
{
	size_t	i;

	i = 0;
	while (i < index)
		free(strs[i++]);
	free(strs);
	return ;
}

char			**ft_split(char const *s, char c)
{
	char	**strs;
	char	*patrol;
	size_t	index;

	index = 0;
	if (!(strs = (char **)malloc(sizeof(char *) * (get_strs_size(s, c) + 1))))
		return (0);
	while (*s)
		if (*s != c)
		{
			patrol = (char *)s;
			while (*patrol && *patrol != c)
				patrol++;
			if (!(strs[index] = (char *)malloc(patrol - s + 1)))
			{
				set_all_memory_null(strs, index - 1);
				return (0);
			}
			ft_strlcpy(strs[index++], (char *)s, patrol - s + 1);
			s = patrol;
		}
		else
			s++;
	strs[index] = 0;
	return (strs);
}

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (s[count])
		count++;
	return (count);
}

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	const unsigned char	*arr1;
	const unsigned char *arr2;

	arr1 = (const unsigned char *)s1;
	arr2 = (const unsigned char *)s2;
	if (n == 0)
		return (0);
	while (n-- > 1)
	{
		if (!(*arr1) || !(*arr2))
			break ;
		if (*arr1 != *arr2)
			break ;
		arr1++;
		arr2++;
	}
	return (*arr1 - *arr2);
}
