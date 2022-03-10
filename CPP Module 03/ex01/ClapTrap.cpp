#include "ClapTrap.hpp"

ClapTrap::ClapTrap(void) : _name("defalut")
{
    std::cout << "ClapTrap default constructor (" << _name << ") called" << std::endl;
    _hitpoints = 10;
    _energyPoints = 10;
    _attackDamage = 10;
}

ClapTrap::ClapTrap(std::string name)
{
    this->_name = name;
    std::cout << "ClapTrap default constructor (" << _name << ") called" << std::endl;
    _hitpoints = 10;
    _energyPoints = 10;
    _attackDamage = 0;
}

ClapTrap::ClapTrap(ClapTrap &src)
{
    this->_name = src._name;
    std::cout << "ClapTrap default constructor (" << _name << ") called" << std::endl;
    this->_hitpoints = src._hitpoints;
    this->_energyPoints = src._energyPoints;
    this->_attackDamage = src._attackDamage;
}

void ClapTrap::attack(std::string const & target)
{
    std::cout << "ClapTrap (" << _name << ") attacks (" << target << ")" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount)
{
	std::cout << "ClapTrap (" << _name << ") has been attacked, " 
	<< "causing <" << amount << "> points of damage!" << std::endl;
	_hitpoints -= amount;
}

void ClapTrap::beRepaired(unsigned int amount)
{
	std::cout << "ClapTrap (" << _name << ") has been repaired, " 
	<< "for <" << amount << "> points!" << std::endl;
	_hitpoints += amount;
}

ClapTrap::~ClapTrap(void)
{
    std::cout << "ClapTrap (" << _name << ") is died" << std::endl;
}
