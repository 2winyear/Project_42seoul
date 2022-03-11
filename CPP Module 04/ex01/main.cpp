#include "Animals.hpp"

int main()
{
    const Animal* j = new Dog();
    const Animal* i = new Cat();

    delete j;
    delete i;

    std::cout << "==========================================" <<std::endl;
    
    Animal* arr[10];
    for (int i = 0; i < 5; i++)
    {
        std::cout << i + 1 << std::endl;
        arr[i] = new Dog();
    }
    for (int i = 5; i < 10; i++)
    {
        std::cout << i + 1 << std::endl;
        arr[i] = new Cat();
    }
    for (int i = 0; i < 10; i++)
    {
        std::cout << i + 1 << std::endl;
        delete arr[i];
    }
    return (0);
}
