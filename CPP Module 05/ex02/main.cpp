#include "Bureaucrat.hpp"
#include "Form.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

void test_form(Form &form, Bureaucrat &correct, Bureaucrat &wrong)
{
    wrong.signForm(form);
    correct.executeForm(form);
    correct.signForm(form);
    wrong.executeForm(form);
    correct.executeForm(form);
}

int main()
{
    srand(time(NULL));

    Bureaucrat seungyel("seungyel", 1);
    Bureaucrat wrong("seungyel", 150);

    ShrubberyCreationForm form1("target");
    RobotomyRequestForm form2("target");
    PresidentialPardonForm form3("target");
    
    test_form(form1, seungyel, wrong);
    test_form(form2, seungyel, wrong);
    test_form(form3, seungyel, wrong);
    return 0;
}
