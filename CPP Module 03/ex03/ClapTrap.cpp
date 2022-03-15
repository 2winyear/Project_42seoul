/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:06:39 by seungyel          #+#    #+#             */
/*   Updated: 2022/03/15 12:06:41 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

ClapTrap::ClapTrap(void) : _name("defalut"), _hitpoints(10), _energyPoints(10), _attackDamage(0)
{
    std::cout << "ClapTrap default constructor (" << _name << ") called" << std::endl;
}

ClapTrap::ClapTrap(std::string name)
{
    this->_name = name;
    std::cout << "ClapTrap string constructor (" << _name << ") called" << std::endl;
    _hitpoints = 10;
    _energyPoints = 10;
    _attackDamage = 0;
}

ClapTrap::ClapTrap(std::string name, int HP, int EP, int AD)
{
    this->_name = name;
    std::cout << "ClapTrap string constructor (" << _name << ") called" << std::endl;
    _hitpoints = HP;
    _energyPoints = EP;
    _attackDamage = AD;
}

ClapTrap &	ClapTrap::operator=(ClapTrap const & src)
{
	_name = src._name;
	_hitpoints = src._hitpoints;
	_energyPoints = src._energyPoints;
	_attackDamage = src._attackDamage;
	std::cout << "ClapTrap operator = (" << _name << ") called" << std::endl;
	return (*this);
}

ClapTrap::ClapTrap(ClapTrap &src)
{
    this->_name = src._name;
    std::cout << "ClapTrap copy constructor (" << _name << ") called" << std::endl;
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

std::string ClapTrap::getName(void)
{
	return (_name);
}

ClapTrap::~ClapTrap(void)
{
    std::cout << "ClapTrap destructor (" << _name << ") called" << std::endl;
}
