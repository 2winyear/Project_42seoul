#include "iter.hpp"

void print_string(std::string &str)
{
	std::cout << str << std::endl;
}

void print_whatever(Whatever &whatever)
{
	std::cout << whatever << std::endl;
}

int main(void)
{
	std::string strs[] = {"Hello", "World", "seungyel", "42Seoul!"};

	iter(strs, sizeof(strs) / sizeof(std::string), print_string);

	Whatever whatever[] = {
		0,
		1,
		2,
		3,
		4,
		5,
		6,
		7,
		8,
		9,
	};

	iter(whatever, sizeof(whatever) / sizeof(Whatever), print_whatever);

	return (0);
}
