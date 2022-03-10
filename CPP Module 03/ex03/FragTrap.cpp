#include "FragTrap.hpp"

FragTrap::FragTrap() : ClapTrap("default", 100, 100, 30)
{
	std::cout << "FragTrap default constructor (" << getName() << ") called" << std::endl;
}


FragTrap::FragTrap(std::string name) : ClapTrap(name, 100, 100, 30)
{
	std::cout << "FragTrap string constructor (" << getName() << ") called" << std::endl;
}

FragTrap::FragTrap(FragTrap &src) : ClapTrap(src)
{
	std::cout << "FragTrap copy constructor (" << getName() << ") called" << std::endl;
}

FragTrap&	FragTrap::operator=(FragTrap const& src)
{
	ClapTrap::operator=(src);
	std::cout << "FragTrap operator = (" << getName() << ") called" << std::endl;
	return (*this);
}

void	FragTrap::highFivesGuys(void)
{
	std::cout << "FragTrap " << getName() << " positive high fives request" << std::endl;
}

FragTrap::~FragTrap()
{
	std::cout << "FragTrap destructor (" << getName() << ") called" << std::endl;
}
