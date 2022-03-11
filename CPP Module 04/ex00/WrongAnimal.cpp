#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal(void) : type("**The FOX**")
{
    std::cout << "Some WrongAnimal just appeared!" << std::endl;
}

WrongAnimal::WrongAnimal(std::string type) : type(type)
{
    std::cout << "Some WrongAnimal just appeared!" << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal &src)
{
    *this = src;
    std::cout << "Some WrongAnimal just appeared!" << std::endl;
}
WrongAnimal::~WrongAnimal()
{
    std::cout << "An WrongAnimal just disappeared!" << std::endl;
}
        
WrongAnimal &WrongAnimal::operator = (const WrongAnimal & other)
{
    this->type = other.type;
    return (*this);
}
        
void WrongAnimal::makeSound(void) const
{
    std::cout << "What does the FOX say?" << std::endl;
    std::cout << "Ring-ding-dong-ring-ding-dong-dingeringeding!" << std::endl;
}

std::string WrongAnimal::getType(void) const
{
    return(type);
}
//Dog Part
WrongDog::WrongDog(void) : WrongAnimal("WrongDog")
{
    std::cout << "Some WrongAnimal "<< getType() << " just appeared!" << std::endl;
}

WrongDog::WrongDog(const WrongDog &src)
{
    *this = src;
    std::cout << "Some WrongAnimal "<< getType() << " just appeared!" << std::endl;
}
WrongDog::~WrongDog()
{
    std::cout << "Some WrongAnimal "<< getType() << " just disappeared!" << std::endl;
}
        
WrongDog &WrongDog::operator = (const WrongDog & other)
{
    this->type = other.type;
    return (*this);
}

void WrongDog::makeSound(void) const
{
    std::cout << "WrongDog goes 'Bow-wow'" << std::endl;
}
// WrongCat Part
WrongCat::WrongCat(void) : WrongAnimal("WrongCat")
{
    std::cout << "Some WrongAnimal "<< getType() << " just appeared!" << std::endl;
}

WrongCat::WrongCat(const WrongCat &src)
{
    *this = src;
    std::cout << "Some WrongAnimal "<< getType() << " just appeared!" << std::endl;
}
WrongCat::~WrongCat()
{
    std::cout << "Some WrongAnimal "<< getType() << " just disappeared!" << std::endl;
}
        
WrongCat &WrongCat::operator = (const WrongCat & other)
{
    this->type = other.type;
    return (*this);
}

void WrongCat::makeSound(void) const
{
    std::cout << "WrongCat goes 'Meow'" << std::endl;
}
