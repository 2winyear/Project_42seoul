#ifndef INTERN_HPP
#define INTERN_HPP
#include <iostream>
#include "Form.hpp"
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"

class Intern {
	private:

	public:
		Intern() {};
		Intern(Intern const &) {};
		Intern &operator=(Intern const &) {return *this;};
		~Intern(){};

		Form *makeForm(std::string const &formName, std::string const &target);

		class NotKnownFormException : public std::exception
		{
			public:
				const char *what() const throw() 
				{
					return ("Intern can't create NotKnownForm");
				}
		};
};

#endif
