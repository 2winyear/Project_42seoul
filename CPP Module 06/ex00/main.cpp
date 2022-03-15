#include "Scalar.hpp"

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cout << "./convert [ Convert Input ]" << std::endl;
		return (1);
	}

	Scalar scalar(argv[1]);
	std::cout << scalar;
	return (0);
}
