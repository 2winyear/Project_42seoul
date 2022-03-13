#include "RobotomyRequestForm.hpp"
#include "Form.hpp"

RobotomyRequestForm::RobotomyRequestForm(std::string const &target) : Form(target, "RobotomyRequestForm", 72, 45)
{
    
}

RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm const &src) : Form(src)
{
    
}

RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &r)
{
    this->Form::operator=(r);
    return (*this);
}

void RobotomyRequestForm::action(Bureaucrat const &executer) const
{
    this->Form::execute(executer);
    std::cout << "\a";

    if (std::rand() % 2 == 0)
        std::cout << this->getTarget() << " is a robot!" << std::endl;
    else
        std::cout << this->getTarget() << " is a human!" << std::endl;
}

RobotomyRequestForm::~RobotomyRequestForm()
{

}
