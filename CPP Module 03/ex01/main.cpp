/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:04:50 by seungyel          #+#    #+#             */
/*   Updated: 2022/03/15 12:04:50 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ScavTrap.hpp"

int main()
{
	ScavTrap	a("a");
	ScavTrap	b("b");

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
	a.guardGate();
	b.guardGate();
}
