#include "Bureaucrat.hpp"
#include "Form.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include "Intern.hpp"

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
	Intern intern;

	Form *form;
    try
	{
		form = intern.makeForm("ShrubberyCreationForm", "target");
		test_form(*form, seungyel, wrong);
		delete form;
		form = intern.makeForm("RobotomyRequestForm", "target");
		test_form(*form, seungyel, wrong);
		delete form;
		form = intern.makeForm("PresidentialPardonForm", "target");
		test_form(*form, seungyel, wrong);
		delete form;
		form = intern.makeForm("WrongName", "target");
		test_form(*form, seungyel, wrong);
		delete form;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	
    return 0;
}
