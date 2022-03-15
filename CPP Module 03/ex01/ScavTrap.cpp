/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScavTrap.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:04:56 by seungyel          #+#    #+#             */
/*   Updated: 2022/03/15 12:04:57 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

ScavTrap::ScavTrap(void) : ClapTrap("default", 100, 50, 20)
{
	std::cout << "ScavTrap default constuctor (" << getName() << ") called" << std::endl;
}

ScavTrap::ScavTrap(std::string name) : ClapTrap(name, 100, 50, 20)
{
	std::cout << "ScavTrap string constuctor (" << getName() << ") called" << std::endl;
}

ScavTrap::ScavTrap(ScavTrap & src) : ClapTrap(src)
{
	std::cout << "ScavTrap copy constructor (" << getName() << ") called" << std::endl;
}

ScavTrap&	ScavTrap::operator=(ScavTrap &src)
{
	ClapTrap::operator=(src);
	std::cout << "ScapTrap operator = (" << getName() << ") called" << std::endl;
	return(*this);
}

ScavTrap::~ScavTrap()
{
	std::cout << "ScavTrap destructor (" << getName() << ") called" << std::endl;
}

void		ScavTrap::guardGate( void )
{
	std::cout << "ScavTrap (" << getName() << ") has enterred in Gate keeper mode." << std::endl;
}
