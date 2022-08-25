#include <stdio.h>
#include <stdlib.h>

int	main(void) 
{
	float	change;
	int		i;

	i = 0;
	change = 0.1;
	while (i < 9)
	{
		change += 0.1;
		i++;
	}
	printf("[ %f ] == COMPARE WITH == [ %f ]\n", change, 0.1 * 10);
	if (change == (0.1 * 10))
		printf("SAME\n");
	else
		printf("It's Not SAME!\n");
	return (0);
}