#include <string>
#include <iostream>
#ifndef ZOMBIE_HPP
#define ZOMBIE_HPP

class Zombie {
	private:
		std::string _name;
	
	public:
		void announce(void);
		void setter_name(std::string);
		Zombie();
		Zombie(std::string);
		~Zombie(void);
};

Zombie* newZombie(std::string);
void randomChump(std::string);
#endif