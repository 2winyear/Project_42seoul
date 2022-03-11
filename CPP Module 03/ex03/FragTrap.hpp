#ifndef FRAGTRAP_HPP
#define FRAGTRAP_HPP
#include "ScavTrap.hpp"

class FragTrap : virtual public ClapTrap { 
	public:
		FragTrap();
		~FragTrap();
		FragTrap(std::string name);
		FragTrap(FragTrap &src);

		FragTrap&	operator=(FragTrap const& src);

		void	highFivesGuys(void);
};

#endif
