/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ClapTrap.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:04:12 by seungyel          #+#    #+#             */
/*   Updated: 2022/03/15 12:04:14 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP
#include <iostream>

class ClapTrap {
    private:
        std::string _name;
        unsigned int _hitpoints;
        unsigned int _energyPoints;
        unsigned int _attackDamage;
    public:
        ClapTrap(void);
        ClapTrap(ClapTrap &src);
        ClapTrap(std::string name);
        ~ClapTrap(void);

        void attack(std::string const & target);
        void takeDamage(unsigned int amount);
        void beRepaired(unsigned int amount);
};

#endif
