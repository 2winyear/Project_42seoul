/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 01:14:29 by seungyel          #+#    #+#             */
/*   Updated: 2022/03/17 16:48:53 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"
#include "Form.hpp"

Bureaucrat::Bureaucrat() : _name("")
{

}

const char* Bureaucrat::GradeTooHighException::what(void) const throw()
{
    return "Bureaucrat Grade Too High";
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
        throw GradeTooLowException();
    if (_grade < GRADE_MIN)
        throw GradeTooHighException();
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
    if (this->_grade - amount < GRADE_MIN)
        throw GradeTooHighException();
    this->_grade -= amount;
}

void Bureaucrat::signForm(Form &form)
{
    try
    {
        form.beSigned(*this);
        std::cout << *this << " signs " << form << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}

void Bureaucrat::decreaseGrade(int amount)
{
    if (this->_grade + amount > GRADE_MAX)
        throw GradeTooLowException();
    this->_grade += amount;
}
        
Bureaucrat &Bureaucrat::operator=(const Bureaucrat & other)
{
    this->_grade = other._grade;
    return (*this);
}

void Bureaucrat::executeForm(Form &form)
{
    try
    {
        form.beSigned(*this);
        std::cout << *this << " signs " << form << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << *this << " cannot sign " << form << " because " << e.what() << '\n';
    }
    
}

std::ostream &operator<<(std::ostream &os, Bureaucrat const &bureaucrat)
{
    os << "[" << bureaucrat.getName() << "] bureaucrat grade : " << bureaucrat.getGrade();
    return (os);
}
