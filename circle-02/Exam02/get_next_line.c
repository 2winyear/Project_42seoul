#include "get_next_line.h"
#include <stdio.h>

int ft_strlen(char *str)
{
	int i = 0;

	while (str[i] != '\0')
	{
		i++;
	}
	return(i);
}

char *ft_strjoin(char* n1, char* n2)
{
	int i = 0;
	int j = 0;
	int n1_len;
	int n2_len;
	char *str;

	n1_len=ft_strlen(n1);
	n2_len=ft_strlen(n2);
	if (!(str = (char*)malloc(sizeof(char)*(n1_len + n2_len + 1))))
		return (NULL);
	while (i < n1_len)
	{
		str[i] = n1[i];
		i++; 
	}
	while (j < n2_len)
		str[i++] = n2[j++];
	str[i] = '\0';
	return (str);
}

int get_next_line(char **line)
{
	char r;	
	char buff[2];
	char *result;

	result = ft_strjoin("","");
	buff[1] = '\0';
	while ((r = read(0, buff, 1)) > 0)
	{
		if (buff[0] == '\n')
		{
			*line = result;
			return (1);
		}
		*line = ft_strjoin(result, buff);
		free(result);
		result = *line;
	}
	if (r < 0)
		return (-1);
	if (r == 0)
	{
		*line = result;
		return (0);
	}
	return (-1);
}

int main(void)
{
	int		r;
	char	*line;

	line = NULL;
	while ((r = get_next_line(&line)) > 0)
	{
		printf("%s\n", line);
		free(line);
		line = NULL;
	}
	printf("%s", line);
	free(line);
	line = NULL;
}