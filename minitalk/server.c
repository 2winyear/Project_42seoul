/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 21:37:24 by seungyel          #+#    #+#             */
/*   Updated: 2021/06/04 00:14:28 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int		g_original;
int		g_count;
int		g_num;
char	g_save[1024];
int		g_index = 0;

void	make_count0(int signum)
{
	g_count--;
	if (g_count < 0)
	{
		g_save[g_index] = g_original;
		g_count = 7;
		g_index++;
		if (g_original == 127)
		{
			write(1, g_save, g_index);
			g_index = 0;
		}
		g_original = 0;
	}
}

void	make_count1(int signum)
{
	int shift;

	shift = 1;
	shift = shift << g_count;
	g_original = g_original | shift;
	g_count--;
	if (g_count < 0)
	{
		g_save[g_index] = g_original;
		g_count = 7;
		g_index++;
		if (g_original == 127)
		{
			write(1, g_save, g_index);
			g_index = 0;
		}
		g_original = 0;
	}
}

int		main(void)
{
	int pid;

	g_count = 7;
	pid = getpid();
	g_original = 0;
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 1);
	signal(SIGUSR1, make_count1);
	signal(SIGUSR2, make_count0);
	while (1)
		;
}
