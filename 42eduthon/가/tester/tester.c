#include "packet_protocol.h"
#include "get_next_line.h"
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

# define B_RED "\033[0;31m"
# define B_YELLOW "\033[1;33m"
# define B_GREEN "\033[0;32m"
# define B_BLUE "\033[1;34m"
# define B_PURPLE "\033[1;35m"
# define B_WHITE "\033[1;37m"
# define EOC "\033[0;0m"

typedef struct s_test_ttt {
	char	*file;
	int		fd;
	char	*line;
	int		result;
}				t_test;

void	print_pass(char *line)
{
	printf("%sPASS:%s ", B_GREEN, EOC);
	printf("%s\n", line);
}

void	print_fail(char *line)
{
	printf("%sFAIL:%s ", B_RED, EOC);
	printf("%s\n", line);
}


int check_space(char *line)
{
	if (line[1] == ' ' && line[3] == ' ')
		return (true);
	return (false);
}

int check_specified(char checked)
{
	if (checked == 'S' || checked == 'E' \
		|| checked == 'R' || checked == 'O' || checked == 'X')
		return (true);
	return (false);
}

int check_params(char *line)
{
	if (('1' <= line[0] && line[0] <= '3') \
		&& ('1' <= line[2] && line[2] <= '3') \
		&& (line[4] == 'O' || line[4] == 'X'))
		return (true);
	else if (line[0] == '-' && line[2] == '-' && check_specified(line[4]))
		return (true);
	return (false);
}

int	check_protocol(char *line)
{
	if (check_params(line) && check_space(line))
		return (true);
	return (false);
}

int	main(int argc, char **argv)
{
	t_test	tst;

	if (argc != 2)
		return (1);
	memset(&tst, 0x00, sizeof(tst));
	tst.file = argv[1];
	tst.fd = open(tst.file, O_RDONLY);
	while (get_next_line(tst.fd, &(tst.line)) > 0)
	{
		if (strlen(tst.line) == 0)
		{
			free(tst.line);
			tst.line = NULL;
			break ;
		}
		if (strlen(tst.line) != 5)
			print_fail(tst.line);
		else if (check_protocol(tst.line) == false)
			print_fail(tst.line);
		else
			print_pass(tst.line);
		free(tst.line);
		tst.line = NULL;
	}
	if (tst.line)
	{
		free(tst.line);
		tst.line = NULL;
	}
	close (tst.fd);
	return (0);
}
