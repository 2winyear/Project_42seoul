#include "PresidentialPardonForm.hpp"
#include "Form.hpp"

PresidentialPardonForm::PresidentialPardonForm() : Form("", "", 42, 42)
{

}

PresidentialPardonForm::PresidentialPardonForm(std::string const &target) : Form(target,"PresidentialPardonForm", 25, 5)
{

}

PresidentialPardonForm::PresidentialPardonForm(PresidentialPardonForm const &src) : Form(src)
{

}
PresidentialPardonForm &PresidentialPardonForm::operator=(PresidentialPardonForm const &other)
{
    this->Form::operator=(other);
    return (*this);
}
PresidentialPardonForm::~PresidentialPardonForm()
{

}
void PresidentialPardonForm::action(Bureaucrat const &executer) const
{
    if (executer.getGrade() > 5)
		throw "execute grade too high";
	this->Form::execute(executer);
    std::cout << "The " << this->getTarget() << " has been pardoned by " << executer.getName() << "." << std::endl;
}
