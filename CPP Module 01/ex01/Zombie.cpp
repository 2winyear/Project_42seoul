/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 01:30:51 by seungyel          #+#    #+#             */
/*   Updated: 2022/02/26 01:30:52 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Zombie.hpp"

Zombie::Zombie()
{

}

Zombie::Zombie(std::string name)
{
	setter_name(name);
}

void Zombie::announce(void)
{
	std::cout << "<" << this->_name << "> BraiiiiiiinnnzzzZ..." << std::endl;
}

void Zombie::setter_name(std::string name)
{
	this->_name = name;
    announce();
}

Zombie::~Zombie(void)
{
	std::cout << this->_name << " is died" << std::endl;
}

Zombie* Zombie::newZombie(std::string name)
{
	Zombie *zombie = new Zombie(name);
	return (zombie);
}