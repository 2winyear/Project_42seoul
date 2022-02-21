#include "Zombie.hpp"

int main()
{
	Zombie zombie1 = Zombie("zombie1 in stack");
	Zombie* zombie2 = newZombie("zombie2 in heap");

	zombie1.announce();
	zombie2->announce();

	randomChump("zombie3 in stack");

	delete zombie2;

	return (0);
}