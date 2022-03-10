#include "FragTrap.hpp"
#include "ScavTrap.hpp"

int main()
{
	FragTrap a("a");
	ScavTrap b("b");

	std::cout << std::endl;
	a.attack("b");
	b.attack("a");
	std::cout << std::endl;
	a.takeDamage(100);
	b.takeDamage(100);
	std::cout << std::endl;
	a.beRepaired(50);
	b.beRepaired(50);
	std::cout << std::endl;
	b.guardGate();
	a.highFivesGuys();
	std::cout << std::endl;
}
