/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   megaphone.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 01:51:22 by seungyel          #+#    #+#             */
/*   Updated: 2022/02/17 01:52:52 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <string>

int main(int argc, char **argv)
{
    if (argc > 1)
    {
		for(int i = 1; i < argc; i++)
		{
			for (int j = 0; j < strlen(argv[i]); j++)
				std::cout << static_cast<char>(toupper(argv[i][j]));
			std::cout << " ";
		}	
    }
    else
        std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *";
    std::cout << std::endl;
	return (0);
}