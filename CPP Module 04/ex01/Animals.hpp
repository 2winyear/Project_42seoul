#ifndef ANIMALS_CPP
# define ANIMALS_CPP

#include "Animals.hpp"
#include <iostream>

class Brain {
    public:
        std::string ideas[100];

        Brain(void);
        Brain(const Brain & src);
        virtual ~Brain();

        Brain &operator =(const Brain &other);
};

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
    private:
        Brain   *brain;

    public:
        Dog(void);
        Dog(const Dog &src);
        virtual ~Dog();
        
        Dog &operator = (const Dog & other);
        
        virtual void makeSound(void) const;
};

class Cat : public Animal{
    private:
        Brain *brain;
    
    public:
        Cat(void);
        Cat(const Cat &src);
        virtual ~Cat();
        
        Cat &operator = (const Cat & other);
        
        virtual void makeSound(void) const;
};
#endif
