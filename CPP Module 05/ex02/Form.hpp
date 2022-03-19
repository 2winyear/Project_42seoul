#ifndef FORM_HPP
#define FORM_HPP
#include "Bureaucrat.hpp"

class Bureaucrat;
class Form {
    private:
        bool sign;
        const std::string target;
        const std::string name;
        const int signGrade;
        const int execGrade;

    public:
        Form(void);
        Form(std::string const &target, std::string const &name, int signGrade, int execGrade);
        Form(Form const &src);
        ~Form();

        Form &operator=(Form const &src);

        std::string getTarget() const;
        std::string getName() const;
        bool getSign() const;
        int getSignGrade() const;
        int getExecGrade() const;
        void beSigned(Bureaucrat const & bureaucrat);
        void execute(Bureaucrat const &executor) const;
        class GradeTooLowException : public std::exception
        {
            public:
                const char *what() const throw(){return("Grade too low");};
        };
        class NoSignedException : public std::exception
        {
            public:
                const char *what() const throw(){return("Not signed");};
        };
};

std::ostream &operator<<(std::ostream &os, Form const &form);

#endif
