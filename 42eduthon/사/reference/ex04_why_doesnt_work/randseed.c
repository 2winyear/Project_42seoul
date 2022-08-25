#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	int	temp;
	int	count;

	srand(100);
	count = 0;
	while (count < 6)
	{
		temp = rand() % 45;
		printf("%5d", temp);
		count++;
	}
	printf("\n");
	return (0);
}