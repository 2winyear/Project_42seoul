#ifndef ANIMAL_CPP
# define ANIMAL_CPP

#include "Animal.hpp"
#include <iostream>

class Animal {
    protected:
        std::string type;
    public:
        Animal(void);
        Animal(std::string type);
        Animal(const Animal &src);
        virtual ~Animal();
        
        Animal &operator = (const Animal & other);
        
        virtual void makeSound(void) const;
        std::string getType(void) const;
};

class Dog : public Animal{
    protected:
    
    public:
        Dog(void);
        Dog(const Dog &src);
        virtual ~Dog();
        
        Dog &operator = (const Dog & other);
        
        virtual void makeSound(void) const;
};

class Cat : public Animal{
    protected:
    
    public:
        Cat(void);
        Cat(const Cat &src);
        virtual ~Cat();
        
        Cat &operator = (const Cat & other);
        
        virtual void makeSound(void) const;
};
#endif
