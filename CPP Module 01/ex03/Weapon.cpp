#include "Weapon.hpp"

Weapon::Weapon()
{
}

Weapon::Weapon(std::string type)
{
    _type = type;
}

Weapon::~Weapon(void)
{

}

std::string &Weapon::getType(void)
{
    return _type;
}

void    Weapon::setType(std::string type)
{
    _type = type;
}