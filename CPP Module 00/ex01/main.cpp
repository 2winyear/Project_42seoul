/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 20:47:28 by seungyel          #+#    #+#             */
/*   Updated: 2022/02/21 16:23:38 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phonebook.hpp"

class PhoneBook {
    private:
        Contact phonebook[8];
        std::string input;
        std::string indexNum;
        int index;
        
    public:
        PhoneBook()
        {
            index = 0;
        }
        void add_phonebook(void)
        {   
            std::cout << "first name" << std::endl;
            getline(std::cin, input);
            phonebook[index].setter_f_name(input);

            std::cout << "last name" << std::endl;
            getline(std::cin, input);
            phonebook[index].setter_l_name(input);

            std::cout << "phone number" << std::endl;
            getline(std::cin, input);
            phonebook[index].setter_phone_number(input);

            std::cout << "nick name" << std::endl;
            getline(std::cin, input);
            phonebook[index].setter_nickname(input);

            std::cout << "darkest secret" << std::endl;
            getline(std::cin, input);
            phonebook[index].setter_darksecret(input);
            index = index % 8;
            index++;
        }

        void search_phonebook()
        {
            (index < 8) ? index : index = 8;
            for(int i = 0 ; i < index ; i++)
            {
                std::cout
                << std::setw(10) << i << "|"
                << std::setw(10) << phonebook[i].getter_f_name() << "|"
                << std::setw(10) << phonebook[i].getter_l_name() << "|"
                << std::setw(10) << phonebook[i].getter_nickname()
                << std::endl; 
            }
        }
};

int main()
{
    PhoneBook phonebook;
    std::string command;
    
    while (1)
    {
        std::cout << "what do you want?(EXIT,ADD,SEARCH)" << std::endl;
        getline(std::cin, command);
        if(command == "EXIT")
        {
            std::cout << "exit" << std::endl;
            return (0);
        }
        else if(command == "ADD")
            phonebook.add_phonebook();
        else if(command == "SEARCH")
            phonebook.search_phonebook();
        else
            std::cout << "wrong answer" << std::endl;
    }
    return (0);
};