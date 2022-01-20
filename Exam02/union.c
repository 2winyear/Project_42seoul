#include <unistd.h>

void ft_putchar(char c)
{
	write(1, &c, 1);
}

int main(int argc, char *argv[])
{
	int i = 0;
	int j = 0;
	int j_2 = 0;
	int i_2 = 0;
	if (argc == 3)
	{
		while (argv[1][i] != '\0')
		{
			j = 0;
			while (j < i)
			{
				if (argv[1][i] == argv[1][j])
					break;
				j++;
			}
			if (j == i)
				ft_putchar(argv[1][i]);
			i++;
		}
		i = 0;
		while (argv[2][i_2] != '\0')
		{
			while (argv[1][i] != '\0')
			{
				if (argv[1][i] == argv[2][i_2])
					break;
				i++;
			}
			j_2 = 0;
			while (j_2 < i_2 && argv[1][i] == '\0')
			{
				if (argv[2][j_2] == argv[2][i_2])
					break;
				j_2++;
			}
			if (j_2 == i_2 && argv[1][i] == '\0')
				ft_putchar(argv[2][j_2]);
			i_2++;
		}
	}
	ft_putchar ('\n');
}