#include "ScavTrap.hpp"

//아 상속했는데 왜 안되는거야
ScavTrap::ScavTrap(void) : ClapTrap()
{
	// _hitpoints = 40;
    // _energyPoints = 40;
    // _attackDamage = 40;
	std::cout << "ScavTrap default constuctor (" << _name << ") called" << std::endl;
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name)
{
	_hitpoints = 40;
    _energyPoints = 40;
    _attackDamage = 40;
}

ScavTrap::~ScavTrap()
{

}