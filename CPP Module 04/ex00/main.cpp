#include "Animal.hpp"
#include "WrongAnimal.hpp"

int main()
{
    const Animal* meta = new Animal();
    const Animal* j = new Dog();
    const Animal* i = new Cat();

    std::cout << j->getType() << " " << std::endl;
    std::cout << i->getType() << " " << std::endl;
    j->makeSound();
    i->makeSound();
    meta->makeSound();

    delete meta;
    delete i;
    delete j;

    std::cout << "==================================" << std::endl;

    const WrongAnimal* Wrongmeta = new WrongAnimal();
    const WrongAnimal* Wrongj = new WrongDog();
    const WrongAnimal* Wrongi = new WrongCat();

    std::cout << Wrongj->getType() << " " << std::endl;
    std::cout << Wrongi->getType() << " " << std::endl;
    Wrongj->makeSound();
    Wrongi->makeSound();
    Wrongmeta->makeSound();

    delete Wrongmeta;
    delete Wrongi;
    delete Wrongj;

    return (0);
}
