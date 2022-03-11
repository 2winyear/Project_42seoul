#ifndef WRONGANIMAL_CPP
# define WRONGANIMAL_CPP

#include "Animal.hpp"
#include <iostream>

class WrongAnimal {
    protected:
        std::string type;
    public:
        WrongAnimal(void);
        WrongAnimal(std::string type);
        WrongAnimal(const WrongAnimal &src);
        ~WrongAnimal();
        
        WrongAnimal &operator = (const WrongAnimal & other);
        
        void makeSound(void) const;
        std::string getType(void) const;
};

class WrongDog : public WrongAnimal{
    protected:
    
    public:
        WrongDog(void);
        WrongDog(const WrongDog &src);
        ~WrongDog();
        
        WrongDog &operator = (const WrongDog & other);
        
        void makeSound(void) const;
};

class WrongCat : public WrongAnimal{
    protected:
    
    public:
        WrongCat(void);
        WrongCat(const WrongCat &src);
        ~WrongCat();
        
        WrongCat &operator = (const WrongCat & other);
        
        void makeSound(void) const;
};
#endif
