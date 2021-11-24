/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 21:37:35 by seungyel          #+#    #+#             */
/*   Updated: 2021/06/03 22:46:52 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	send_char(int pid, char input)
{
	int tmp;
	int shift;

	shift = 1 << 7;
	while (shift >= 1)
	{
		tmp = input & shift;
		if (tmp == shift)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		shift = shift >> 1;
		usleep(100);
	}
}

void	send_str(int pid, char input[])
{
	int	i;

	i = 0;
	while (input[i] != '\0')
	{
		send_char(pid, input[i]);
		i++;
	}
	send_char(pid, 127);
}

int		main(int argc, char *argv[])
{
	int		pid;
	char	input;

	pid = ft_atoi(argv[1]);
	send_str(pid, argv[2]);
}
