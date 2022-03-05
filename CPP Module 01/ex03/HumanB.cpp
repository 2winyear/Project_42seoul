#include "HumanB.hpp"

HumanB::HumanB(std::string name) : _name(name), _weapon(NULL)
{

}

HumanB::~HumanB()
{

}

void    HumanB::attack(void)
{
    if(_weapon == NULL)
        std::cout << "fist" << std::endl;
    else
        std::cout << this->_name << " " << this->_weapon->getType() << " " << std::endl;
}

void    HumanB::setWeapon(Weapon &weapon)
{
    _weapon = &weapon;
}