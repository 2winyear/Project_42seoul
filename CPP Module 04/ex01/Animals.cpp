#include "Animals.hpp"
//Brain Part
Brain::Brain(void)
{
    std::cout << "New Brain!" << std::endl;
}

Brain::Brain(const Brain &src)
{
    *this = src;
    std::cout << "New Brain!" << std::endl;
}

Brain::~Brain(void)
{
    std::cout << "--No Brain!" << std::endl;
}

Brain& Brain::operator=(const Brain &other)
{
    for (int i = 0 ; i < 100 ; i++)
        this->ideas[i] = other.ideas[i];
    return(*this);
}
//Animal Part
Animal::Animal(void) : type("**The FOX**")
{
    std::cout << "Some Animal just appeared!" << std::endl;
}

Animal::Animal(std::string type) : type(type)
{
    std::cout << "Some Animal just appeared!" << std::endl;
}

Animal::Animal(const Animal &src)
{
    *this = src;
    std::cout << "Some Animal just appeared!" << std::endl;
}
Animal::~Animal()
{
    std::cout << "An Animal just disappeared!" << std::endl;
}
        
Animal &Animal::operator = (const Animal & other)
{
    this->type = other.type;
    return (*this);
}
        
void Animal::makeSound(void) const
{
    std::cout << "What does the FOX say?" << std::endl;
    std::cout << "Ring-ding-dong-ring-ding-dong-dingeringeding!" << std::endl;
}

std::string Animal::getType(void) const
{
    return(type);
}
//Dog Part
Dog::Dog(void) : Animal("Dog")
{
    brain = new Brain();
    std::cout << "Some Animal "<< getType() << " just appeared!" << std::endl;
}

Dog::Dog(const Dog &src)
{
    *this = src;
    std::cout << "Some Animal "<< getType() << " just appeared!" << std::endl;
}
Dog::~Dog()
{
    delete brain;
    std::cout << "Some Animal "<< getType() << " just disappeared!" << std::endl;
}
        
Dog &Dog::operator = (const Dog & other)
{
    this->type = other.type;
	this->brain = other.brain;
    return (*this);
}

void Dog::makeSound(void) const
{
    std::cout << "Dog goes 'Bow-wow'" << std::endl;
}
// Cat Part
Cat::Cat(void) : Animal("Cat")
{
    brain = new Brain();
    std::cout << "Some Animal "<< getType() << " just appeared!" << std::endl;
}

Cat::Cat(const Cat &src)
{
    *this = src;
    std::cout << "Some Animal "<< getType() << " just appeared!" << std::endl;
}
Cat::~Cat()
{
    delete brain;
    std::cout << "Some Animal "<< getType() << " just disappeared!" << std::endl;
}
        
Cat &Cat::operator = (const Cat & other)
{
    this->type = other.type;
    return (*this);
}

void Cat::makeSound(void) const
{
    std::cout << "Cat goes 'Meow'" << std::endl;
}
