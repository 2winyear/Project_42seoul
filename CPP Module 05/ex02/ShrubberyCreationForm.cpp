#include "ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm() : Form("", "", 42, 42)
{

}

ShrubberyCreationForm::ShrubberyCreationForm(std::string const &target) : Form(target, "ShrubberyCreationForm", 145, 137)
{
    
}
ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm &src) : Form(src)
{

}
ShrubberyCreationForm &ShrubberyCreationForm::operator=(ShrubberyCreationForm &s)
{
    this->Form::operator=(s);
    return (*this);
}
ShrubberyCreationForm::~ShrubberyCreationForm()
{

}
void ShrubberyCreationForm::action(Bureaucrat const &executer) const
{
    this->Form::execute(executer);
    std::ofstream file(this->getTarget()+"_shrubbery");

    if (file.is_open() == false)
        throw std::ofstream::failure("Could not open file " + this->getTarget() + "_shrubbery");
    file << ASCIISPADE;
}
