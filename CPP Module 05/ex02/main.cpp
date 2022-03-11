#include "Bureaucrat.hpp"
#include "Form.hpp"

int main()
{
    Bureaucrat seungyel("seungyel", 50);
    try
    {
        seungyel.increaseGrade(9);
        std::cout << seungyel << std::endl;
        seungyel.increaseGrade(1);
        std::cout << seungyel << std::endl;
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    Form formA("a", 10, 10);
    Form formB("b", 10, 10);
    seungyel.signForm(formA);
    seungyel.decreaseGrade(10);
    seungyel.signForm(formB);
    std::cout << formA << std::endl;
    std::cout << formB << std::endl;
    return 0;
}
