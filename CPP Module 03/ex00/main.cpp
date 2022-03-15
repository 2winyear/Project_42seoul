/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:04:21 by seungyel          #+#    #+#             */
/*   Updated: 2022/03/15 12:04:23 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ClapTrap.hpp"

int main()
{
    ClapTrap    a("a");
    ClapTrap    b("b");
    ClapTrap    c;

    a.attack("b");
	a.beRepaired(100);
	a.takeDamage(100);
}
