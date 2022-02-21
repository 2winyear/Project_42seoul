#include "Zombie.hpp"

Zombie::Zombie()
{

}

Zombie::Zombie(std::string name)
{
	setter_name(name);
}

Zombie::~Zombie(void)
{
	std::cout << this->_name << " is died" << std::endl;
}

void Zombie::announce(void)
{
	std::cout << "<" << this->_name << "> BraiiiiiiinnnzzzZ..." << std::endl;
}

void Zombie::setter_name(std::string name)
{
	this->_name = name;
}