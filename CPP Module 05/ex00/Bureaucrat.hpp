/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Bureaucrat.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 01:14:39 by seungyel          #+#    #+#             */
/*   Updated: 2022/03/14 01:16:58 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP
#include <iostream>
#include <string>
#include <stdexcept>
#define GRADE_MAX 150
#define GRADE_MIN 1

class Bureaucrat {
    private:
        const std::string _name;
        int _grade;
    public:
        Bureaucrat();
        Bureaucrat(std::string const name, int grade);
        ~Bureaucrat();
        int getGrade(void)const;
        void increaseGrade(int amount);
        void decreaseGrade(int amount);

        std::string const & getName(void)const;
        Bureaucrat &    operator=(const Bureaucrat & other);

        class GradeTooLowException : public std::exception
        {
           const char * what(void) const throw();
        };
        class GradeTooHighException : public std::exception
        {
            const char * what(void) const throw();
        };
};

std::ostream &  operator << (std::ostream &stream, const Bureaucrat &bureaucrat);

#endif
