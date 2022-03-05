/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 01:32:25 by seungyel          #+#    #+#             */
/*   Updated: 2022/02/28 01:35:41 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

int main()
{
    std::string brain = "HI THIS IS BRAIN";

    std::string *stringPTR = &brain;
    std::string &stringREF = brain;

    std::cout << "Address of original string : " << stringPTR <<std::endl;
    std::cout << "Address of the string in PTR : " << stringPTR <<std::endl;
    std::cout << "Address of the string in REF : " << &stringREF <<std::endl;
    return (0);
}