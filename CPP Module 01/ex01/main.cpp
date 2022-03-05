/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/26 01:30:18 by seungyel          #+#    #+#             */
/*   Updated: 2022/03/01 06:31:07 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	해야할일: 좀비들 이름 바꾸기
*/


#include "Zombie.hpp"

int	ft_isspace(char c)
{
	if (c == '\n' || c == '\t' || c == '\v' ||
			c == '\r' || c == '\f' || c == ' ')
		return (1);
	else
		return (0);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	value;

	i = 0;
	value = 0;
	sign = 1;
	while ((str[i] != '\0') && (ft_isspace(str[i]) == 1))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0' && (str[i] >= '0' && str[i] <= '9'))
	{
		value = value * 10 + (str[i] - '0');
		i++;
	}
	return (sign * value);
}

int main()
{
	int N;
	std::string num;
	std::string name = "seungyel";

	std::cout << "How many Zombies do you want?" << std::endl;
	getline(std::cin, num);
	
	N = ft_atoi(num.c_str());
	std::cout << atoi(num.c_str()) << std::endl;
	
	//이부분 왜 오류나냐
	Zombie *z = z->zombieHorde(N, name);
	delete[] z;

	return (0);
}