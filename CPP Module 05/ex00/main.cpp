/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 01:14:19 by seungyel          #+#    #+#             */
/*   Updated: 2022/03/14 01:14:21 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Bureaucrat.hpp"

int main()
{
    try
    {
        Bureaucrat seungyel("seungyel", 50);

        seungyel.increaseGrade(9);
        std::cout << seungyel << std::endl;
        seungyel.decreaseGrade(39);
        std::cout << seungyel << std::endl;
        seungyel.increaseGrade(80);
        std::cout << seungyel << std::endl;
    }
    catch(std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
