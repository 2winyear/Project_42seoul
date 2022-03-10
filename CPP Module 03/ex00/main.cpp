#include "ClapTrap.hpp"

int main()
{
    ClapTrap    a("a");
    ClapTrap    b("b");
    ClapTrap    c;

    a.attack("b");
	a.beRepaired(100);
	a.takeDamage(100);
}
