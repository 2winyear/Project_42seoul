#include <unistd.h>

int	main()
{
	while(write(1, "y\n", 2));
	return 0;
}
