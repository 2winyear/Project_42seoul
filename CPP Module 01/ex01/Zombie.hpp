#include <string>
#include <iostream>
#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

class Zombie {
	private:
		std::string _name;
	
	public:
		Zombie* zombieHorde(int N, std::string name);
};

#endif