#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	do_child(void)
{
	while (1) 
	{
		printf("[%d] %s", getpid(), "Brrrraaaaiiinnnzzz...\n");
		sleep(2);
	}
}

int	main(void)
{
	pid_t	pid;

	pid = fork();
	if (!pid) 
		do_child();
	else
		waitpid(-1, NULL, WNOHANG);
	printf("[%d] GoodBye! I'm Running! -by main \n", getpid());
	return 0;
}