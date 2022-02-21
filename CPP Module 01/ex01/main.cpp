#include "Zombie.hpp"

int main()
{
	int num;
	std::string name = "";
	
	std::cout << "How many Zombies do you want?" << std::endl;
	getline(std::cin, num);
	zombieHorde(num, name);
}