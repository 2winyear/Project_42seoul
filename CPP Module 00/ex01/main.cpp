/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/20 20:47:28 by seungyel          #+#    #+#             */
/*   Updated: 2022/02/20 20:47:30 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phonebook.hpp"

int main()
{
    Contact phonebook[8];
    std::string indexNum;
    std::string command;
    std::string input;
    int index = 0;

    /*
    클래스가 두개여야된다는데>?
    */

    while (1)
    {
        std::cout << "what do you want?" << std::endl;
        getline(std::cin, command);
        if(command == "EXIT")
        {
            std::cout << "exit" << std::endl;
            return (0);
        }
        else if(command == "ADD")
        {
            //뭔가 이상하긴 하지만,,?
            indexNum = phonebook[index].ft_itoa(index);
            phonebook[index].setter_index(indexNum);

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

            index++;
            if (index == 8)
                index = 0;
        }
        else if(command == "SEARCH")
        {
            for(int i = 0 ; i < 8 ; i++)
            {
                if(phonebook[i].getter_index() == "\0")
                    return(0);
                std::cout
                << std::setw(10) << phonebook[i].getter_index() << "|"
                << std::setw(10) << phonebook[i].getter_f_name() << "|"
                << std::setw(10) << phonebook[i].getter_l_name() << "|"
                << std::setw(10) << phonebook[i].getter_nickname()
                << std::endl; 
            }
        }
        else
            std::cout << "wrong answer" << std::endl;
    }
};