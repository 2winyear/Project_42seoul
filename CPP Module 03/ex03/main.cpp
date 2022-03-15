/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:06:15 by seungyel          #+#    #+#             */
/*   Updated: 2022/03/15 15:42:32 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "FragTrap.hpp"
#include "ScavTrap.hpp"
#include "DiamondTrap.hpp"

int main()
{
	DiamondTrap a("a");
	DiamondTrap b("b");

	std::cout << std::endl;
	a.attack("b");
	a.whoAmI();
	std::cout << std::endl;

	return (0);
}
