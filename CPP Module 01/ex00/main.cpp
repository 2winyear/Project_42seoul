#include "Zombie.hpp"

int main()
{
	Zombie zombie1 = Zombie("zombie1 in stack");
	Zombie* zombie2 = newZombie("zombie2 in heap");

	zombie1.announce();
	zombie2->announce();

	return (0);
}