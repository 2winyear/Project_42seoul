#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP
#include <iostream>
#include <string>
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
        ClapTrap(std::string name, int HP, int EP, int AD);
        ~ClapTrap(void);

		ClapTrap	&operator=(ClapTrap const & src);
		std::string getName(void);

        void attack(std::string const & target);
        void takeDamage(unsigned int amount);
        void beRepaired(unsigned int amount);
};

#endif
