#include "PresidentialPardonForm.hpp"
#include "Form.hpp"

PresidentialPardonForm::PresidentialPardonForm(std::string const &target) : Form(target,"PresidentialPardonForm", 72, 45)
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
    this->Form::execute(executer);
    std::cout << "The " << this->getTarget() << " has been pardoned by " << executer.getName() << "." << std::endl;
}
