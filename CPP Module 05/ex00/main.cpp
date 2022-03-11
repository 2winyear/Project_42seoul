#include "Bureaucrat.hpp"

int main()
{
    try
    {
        Bureaucrat seungyel("seungyel", 50);
        seungyel.increaseGrade(9);
        std::cout << seungyel << std::endl;
        seungyel.increaseGrade(1);
        std::cout << seungyel << std::endl;
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
