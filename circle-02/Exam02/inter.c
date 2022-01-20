#include <unistd.h>

void ft_putchar(char c)
{
	write(1, &c, 1);
}

int main(int argc, char *argv[])
{
	int i = 0;
	int j = 0;
	int index;

	if (argc == 3)
	{
		while (argv[1][i] != '\0')
		{
			index = 0;
			while (index < i)
			{					
				if (argv[1][index] == argv[1][i])
					break;
				index++;
			}
			j = 0;
			while (argv[2][j] != '\0' && index == i)
			{
				if (argv[1][i] == argv[2][j])
				{
					ft_putchar(argv[1][i]);
					break;
				}
				j++;
			}
			i++;
		}
	}
	ft_putchar('\n');
}
