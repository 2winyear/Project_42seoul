#ifndef FORM_HPP
#define FORM_HPP
#include "Bureaucrat.hpp"

class Bureaucrat;
class Form {
    private:
        const std::string name;
        bool sign;
        const int signGrade;
        const int execGrade;
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
