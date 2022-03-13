#ifndef FORM_HPP
#define FORM_HPP
#include "Bureaucrat.hpp"

class Bureaucrat;
class Form {
    private:
        bool sign;
        const std::string name;
        const int signGrade;
        const int execGrade;
        Form(void):name(""), signGrade(42), execGrade(42){};
    public:
        Form(std::string const &name, int signGrade, int execGrade);
        Form(Form const &src);
        ~Form();

        Form &operator=(Form const &src);

        std::string getName() const;
        bool getSign() const;
        int getSignGrade() const;
        int getExecGrade() const;
        void beSigned(Bureaucrat const & bureaucrat);
        class GradeTooLowException : public std::exception
        {
            const char *what() const throw();
        };
};

std::ostream &operator<<(std::ostream &os, Form const &form);

#endif
