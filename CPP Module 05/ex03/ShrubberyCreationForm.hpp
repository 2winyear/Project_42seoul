#ifndef SHRUBERYCREATIONFORM_HPP
# define SHRUBERYCREATIONFORM_HPP
#include <fstream>
#include "Bureaucrat.hpp"
#include "Form.hpp"

#define ASCIISPADE "\
.   .  ..  .   .  ..-*..  ..  .   .  ..  .\n\
   .  .   .   .  .  @@   .  .   .   .  .  \n\
  ..  .   .   .  . #@@@  .  .   .   .  .  \n\
.   .  ..  .   .  ~@@@@#  ..  .   .  ..  .\n\
                 -@@@@@@-                 \n\
                 @@@@@@@@-                \n\
  ..  .   .   . @@@@@@@@@@  .   .   .  .  \n\
.   .  ..  .   @@@@@@@@@@@@.  .   .   .  .\n\
.   .  ..  .  @@@@@@@@@@@@@@  .   .   .  .\n\
  ..  .   .  @@@@@@@@@@@@@@@@,  .   .  .  \n\
   .  .   . @@@@@@@@@@@@@@@@@@  .   .  .  \n\
           @@@@@@@@@@@@@@@@@@@@           \n\
.   .  .. :@@@@@@@@@@@@@@@@@@@@!  .  ..  .\n\
  ..  .   @@@@@@@@@@@@@@@@@@@@@@.   .  .  \n\
   .  .  ;@@@@@@@@@@@@@@@@@@@@@@!   .  .  \n\
         #@@@@@@@@@@@@@@@@@@@@@@*         \n\
.   .  ..@@@@@@@@@@@@@@@@@@@@@@@@ .  ..  .\n\
         @@@@@@@@@@@@@@@@@@@@@@@*         \n\
  ..  .  ;@@@@@@@@@@@@@@@@@@@@@@;   .  .  \n\
.   .  ...@@@@@@@@@@@@@@@@@@@@@@  .  ..  .\n\
          :@@@@@@@@@@@@@@@@@@@@.          \n\
            @@@@@@@;@@.#@@@@@!            \n\
  ..  .   .   .~ .  @@*  .  .   .   .  .  \n\
.   .  .   .   .   #@@@   .   .   .       \n\
.   .  ..  .   .  .@@@@,  ..  .   .  ..  .\n\
  ..  .   .   .  .~@@@@@ .  .   .   .  .  \n\
   .  .   .   .   @@@@@@;.  .   .   .  .  \n\
                 !!!!!!!!                 \n\
.   .  ..  .   .  ..  ..  ..  .   .  ..  .\n\
   .  .   .   .  .   .   .  .   .   .  .  \n\
"

class ShrubberyCreationForm : public Form {
    private:
    public:
        static const int    Grade2Sign;
        static const int    Grade2exec;

        ShrubberyCreationForm();
        ShrubberyCreationForm(std::string const &target);
        ShrubberyCreationForm(ShrubberyCreationForm &src);
        ShrubberyCreationForm &operator=(ShrubberyCreationForm &s);
        ~ShrubberyCreationForm();

        void action(Bureaucrat const &executor) const;
		static Form *create(std::string const &target);
};

#endif
