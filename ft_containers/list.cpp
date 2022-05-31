#include <list>
#include "list.hpp"

int main()
{
	std::list<int> origin(5);
	std::list<int>::iterator it;

	for (it = origin.begin(); it != origin.end(); it++)
		std::cout << *it << " ";
	std::cout << std::endl;

	return (0);
}