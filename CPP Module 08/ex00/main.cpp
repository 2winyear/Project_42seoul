/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 14:54:08 by seungyel          #+#    #+#             */
/*   Updated: 2022/03/22 14:54:09 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "easyfind.hpp"

int main(void)
{
	std::vector<int> test1;
	std::deque<int> test2;

	for (int i = 0 ; i < 10 ; i++)
	{
		test1.push_back(i);
		test2.push_back(i + 10);
	}
	try
	{
		std::cout << *(::easyfind(test1,1)) << std::endl;
		std::cout << *(::easyfind(test1,7)) << std::endl;
		std::cout << *(::easyfind(test2,16)) << std::endl;
		std::cout << *(::easyfind(test2,42)) << std::endl;
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	return (0);
}
