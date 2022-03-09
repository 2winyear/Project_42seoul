/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Zombie.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 01:31:03 by seungyel          #+#    #+#             */
/*   Updated: 2022/03/01 05:38:20 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string>
#include <iostream>
#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

class Zombie {
	private:
		std::string _name;
	
	public:
		Zombie();
		Zombie(std::string);
		~Zombie(void);
		void announce(void);
		void setter_name(std::string);
		Zombie* newZombie(std::string);
};
Zombie* zombieHorde(int, std::string);

#endif