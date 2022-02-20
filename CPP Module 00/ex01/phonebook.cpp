/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phonebook.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 20:47:21 by seungyel          #+#    #+#             */
/*   Updated: 2022/02/20 20:47:22 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phonebook.hpp"

void Contact::setter_index(std::string _index)
{
    this->_index = _index;
}

void Contact::setter_f_name(std::string _f_name)
{
    this->_first_name = _f_name;
}

void Contact::setter_l_name(std::string _l_name)
{
    this->_last_name = _l_name;
}

void Contact::setter_phone_number(std::string _phone)
{
    this->_phone = _phone;
}

void Contact::setter_nickname(std::string _nickname)
{
    this->_nick_name = _nickname;
}

void Contact::setter_darksecret(std::string _darksecret)
{
    this->_secret = _darksecret;
}

std::string Contact::ft_itoa(int index)
{
    switch (index)
    {
    case 0:
        return ("0");
    case 1:
        return ("1");
    case 2:
        return ("2");
    case 3:
        return ("3");
    case 4:
        return ("4");
    case 5:
        return ("5");
    case 6:
        return ("6");
    case 7:
        return ("7");
    default:
        return("8");
    }
}

std::string Contact::getter_index(void)
{
    return (this->_index);
}

std::string Contact::getter_f_name(void)
{
    return (this->_first_name);
}

std::string Contact::getter_l_name(void)
{
    return (this->_last_name);
}

std::string Contact::getter_nickname(void)
{
    return (this->_nick_name);
}