#include "Base.hpp"

int main()
{
	srand(time(NULL));
	for (int i = 0; i < 10; i++)
	{
		Base *p = generate();
		identify(p);
	}
	return (0);
}
