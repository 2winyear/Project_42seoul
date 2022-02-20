/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 20:47:15 by seungyel          #+#    #+#             */
/*   Updated: 2022/02/20 23:35:13 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP
class Contact {
    private :
        std::string _first_name; 
        std::string _last_name;
        std::string _nick_name;
        std::string _phone;
        std::string _secret;
    
    public:
        void setter_command(std::string);
        void setter_index(std::string);
        void setter_f_name(std::string);
        void setter_l_name(std::string);
        void setter_phone_number(std::string);
        void setter_nickname(std::string);
        void setter_darksecret(std::string);
        std::string getter_index(void);
        std::string getter_command(void);
        std::string getter_f_name(void);
        std::string getter_l_name(void);
        std::string getter_nickname(void);
        std::string ft_itoa(int);
};

#endif