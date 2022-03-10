#ifndef SCAVTRAP_HPP
# define SCAVTRAP_HPP
# include "ClapTrap.hpp"

class ScavTrap: public ClapTrap {
	protected:
		
	public:
		ScavTrap(void);
		ScavTrap(std::string name);
		ScavTrap(ScavTrap & src);
		~ScavTrap();

		ScavTrap&	operator=(ScavTrap &src);

		void	guardGate(void);
};

#endif
