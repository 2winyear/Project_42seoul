#include "Bureaucrat.hpp"
#include "Form.hpp"

Bureaucrat::Bureaucrat() : _name("")
{

}

const char* Bureaucrat::GradeTooHighException::what(void) const throw()
{
    return "Bureaucrat Grade Too High";
}

void Bureaucrat::signForm(Form &form)
{
    try
    {
        form.beSigned(*this);
        std::cout << *this << " signs" << form << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cout << *this << " connot sign " << form << " because " << e.what() << std::endl;
    }
}

const char* Bureaucrat::GradeTooLowException::what(void) const throw()
{
    return "Bureaucrat Grade Too Low";
}

std::string const & Bureaucrat::getName(void) const
{
    return _name;
}

Bureaucrat::Bureaucrat(std::string const name, int grade) : _name(name), _grade(grade)
{
    if (_grade > GRADE_MAX)
        throw GradeTooHighException();
    if (_grade < GRADE_MIN)
        throw GradeTooLowException();
}

Bureaucrat::~Bureaucrat()
{

}

int Bureaucrat::getGrade(void)const
{
    return (_grade);
}

void Bureaucrat::increaseGrade(int amount)
{
    if (this->_grade - amount <= GRADE_MIN)
        throw GradeTooHighException();
    if (this->_grade - amount >= GRADE_MAX)
        throw GradeTooLowException();
    this->_grade -= amount;
}

void Bureaucrat::decreaseGrade(int amount)
{
    if (this->_grade + amount <= GRADE_MIN)
        throw GradeTooHighException();
    if (this->_grade + amount >= GRADE_MAX)
        throw GradeTooLowException();
    this->_grade += amount;
}
        
Bureaucrat &Bureaucrat::operator=(const Bureaucrat & other)
{
    this->_grade = other._grade;
    return (*this);
}

std::ostream &operator<<(std::ostream &os, Bureaucrat const &bureaucrat)
{
    os << bureaucrat.getName() << ", bureaucrat grade " << bureaucrat.getGrade();
    return (os);
}
