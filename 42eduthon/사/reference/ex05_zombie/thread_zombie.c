#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	*routine(void *s)
{
	while (1)
	{
		write(1, "aa\n", 3);
		sleep(1);
	}
	return (NULL);
}

int	main(void)
{
	pthread_t	*thread;

	pthread_create(thread, NULL, routine, NULL);
	return (0);
}