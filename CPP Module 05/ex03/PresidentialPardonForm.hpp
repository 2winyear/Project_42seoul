#ifndef PRESIDENTIALPARDONFORM_HPP
# define PRESIDENTIALPARDONFORM_HPP

#include "Form.hpp"
#include "Bureaucrat.hpp"

class Bureaucrat;
class PresidentialPardonForm : public Form {
    private:
        PresidentialPardonForm() : Form("", "", 42, 42){};
    public:
        PresidentialPardonForm(std::string const &target);
        PresidentialPardonForm(PresidentialPardonForm const &src);
        PresidentialPardonForm &operator=(PresidentialPardonForm const &other);
        ~PresidentialPardonForm();
        
        void action(Bureaucrat const &executer) const;
		static Form *create(std::string const &target);
};

#endif
