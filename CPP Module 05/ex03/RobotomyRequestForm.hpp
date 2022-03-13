#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP
#include <cstdlib>
#include "Form.hpp"

class RobotomyRequestForm : public Form {
    private:
        RobotomyRequestForm() : Form("", "", 42, 42){};
    public:
        void action(Bureaucrat const &executer) const;
        RobotomyRequestForm(std::string const &target);
        RobotomyRequestForm(RobotomyRequestForm const &src);
        RobotomyRequestForm &operator=(const RobotomyRequestForm &r);
        ~RobotomyRequestForm();
};

#endif
