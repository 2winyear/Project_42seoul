#ifndef ANIMALS_CPP
# define ANIMALS_CPP

#include "Animals.hpp"
#include <iostream>


class Animal {
    protected:
        std::string type;
        Animal(void);
    public:
        Animal(std::string type);
        Animal(const Animal &src);
        virtual ~Animal();
        
        Animal &operator = (const Animal & other);
        
        virtual void makeSound(void) const = 0;
        std::string getType(void) const;
};

class Dog : public Animal{
    private:

    public:
        Dog(void);
        Dog(const Dog &src);
        virtual ~Dog();
        
        Dog &operator = (const Dog & other);
        
        virtual void makeSound(void) const;
};

class Cat : public Animal{
    private:
    
    public:
        Cat(void);
        Cat(const Cat &src);
        virtual ~Cat();
        
        Cat &operator = (const Cat & other);
        
        virtual void makeSound(void) const;
};
#endif
