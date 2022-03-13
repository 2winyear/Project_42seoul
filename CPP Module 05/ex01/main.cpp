#include "Bureaucrat.hpp"
#include "Form.hpp"
#include "ShrubberyCreationForm.hpp"

int main()
{
    srand(time(NULL));
    Bureaucrat seungyel("seungyel", 10);
    Bureaucrat wrong("wrong", 10);

    ShrubberyCreationForm form("target");

    Form formA("a", 100, 10);
    Form formB("b", 10, 100);
    Form formC("c", 10, 10);

    try
    {
        seungyel.signForm(formA);
        seungyel.signForm(formB);
        seungyel.signForm(formC);
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    std::cout << formA << std::endl;
    std::cout << formB << std::endl;
    std::cout << formC << std::endl;

    return 0;
}
