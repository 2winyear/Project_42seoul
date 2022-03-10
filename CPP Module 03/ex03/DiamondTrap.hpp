#ifndef DIAMONDTRAP_HPP
# define DIAMONDTRAP_HPP
# include "FragTrap.hpp"
# include "ClapTrap.hpp"
# include "ScavTrap.hpp"

//public ClapTrap는 왜 상속 안하는거지
class DiamondTrap : public ScavTrap, public FragTrap {
	private:
		std::string _name;
	public:
		DiamondTrap();
		DiamondTrap(std::string name);
		DiamondTrap(std::string name, int HP, int EP, int AD);
		DiamondTrap(DiamondTrap &src);
		~DiamondTrap();

		DiamondTrap &operator = (DiamondTrap &src);

		void	whoAmI(void);
};

#endif
