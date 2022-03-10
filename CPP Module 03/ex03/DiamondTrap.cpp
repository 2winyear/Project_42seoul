#include "DiamondTrap.hpp"

//? ClapTrap을 class에서 상속해오지 않았는데 어떻게 사용하는거지
DiamondTrap::DiamondTrap() : ClapTrap()
{
	std::cout << "DiamondTrap default constructor (" << _name << ") called" << std::endl;
}

DiamondTrap::DiamondTrap(std::string name) : ClapTrap(name + "_clap_name"), ScavTrap(name), FragTrap(name)
{
	std::cout << "DiamondTrap string constructor (" << _name << ") called" << std::endl;
}

DiamondTrap::DiamondTrap(DiamondTrap &src) : ClapTrap(src), ScavTrap(src), FragTrap(src)
{
	std::cout << "DiamondTrap copy constructor (" << _name << ") called" << std::endl;
}

DiamondTrap::DiamondTrap(std::string name, int HP, int EP, int AD) :
				ClapTrap(name, HP, EP, Ad), _name(name)
{

}

DiamondTrap &DiamondTrap::operator = (DiamondTrap &src)
{
	ScavTrap::operator=(src);
	std::cout << "DiamondTrap operator = (" << _name << ") called" << std::endl;
	return (*this);
}

void	DiamondTrap::whoAmI(void)
{
	std::cout << "This DiamondTrap name is " << _name << std::endl
	<< " and This ClapTrap name is " << ClapTrap::getName << std::endl;
}

DiamondTrap::~DiamondTrap()
{
	std::cout << "DiamondTrap destructor (" << _name << ") called" << std::endl;
}