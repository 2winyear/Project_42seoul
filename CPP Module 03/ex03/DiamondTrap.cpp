/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   DiamondTrap.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:06:32 by seungyel          #+#    #+#             */
/*   Updated: 2022/03/15 15:39:05 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "DiamondTrap.hpp"

DiamondTrap::DiamondTrap() : ClapTrap()
{
	std::cout << "DiamondTrap default constructor (" << _name << ") called" << std::endl;
}

DiamondTrap::DiamondTrap(std::string name) : ClapTrap(name + "_clap_name"), ScavTrap(name), FragTrap(name)
{
	this->_name = name;
	std::cout << "DiamondTrap string constructor (" << _name << ") called" << std::endl;
}

DiamondTrap::DiamondTrap(DiamondTrap &src) : ClapTrap(src), ScavTrap(src), FragTrap(src)
{
	std::cout << "DiamondTrap copy constructor (" << _name << ") called" << std::endl;
}

DiamondTrap::DiamondTrap(std::string name, int HP, int EP, int AD) :
				ClapTrap(name, HP, EP, AD), _name(name)
{
	this->_name = name;
	std::cout << "DiamondTrap copy constructor (" << _name << ") called" << std::endl;
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
	<< " and This ClapTrap name is " << ClapTrap::getName() << std::endl;
}

DiamondTrap::~DiamondTrap()
{
	std::cout << "DiamondTrap destructor (" << _name << ") called" << std::endl;
}
