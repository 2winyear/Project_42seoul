/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:45:52 by seungyel          #+#    #+#             */
/*   Updated: 2021/12/02 12:19:08 by byeukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_flag(char *command)
{
	int	idx;

	idx = 0;
	if (command[idx] != '-')
		return (1);
	while (command[++idx])
	{
		if (command[idx] != 'n')
			return (1);
	}
	return (0);
}

void	ft_echo(char **command)
{
	int	idx;
	int	flag;

	idx = 0;
	flag = 0;
	while (!check_flag(command[idx + 1]))
	{	
		flag = 1;
		idx += 1;
	}
	while (command[++idx])
		printf("%s ", command[idx]);
	printf("\b");
	if (flag != 1)
		printf("\n");
}
