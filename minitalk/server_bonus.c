/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 21:37:24 by seungyel          #+#    #+#             */
/*   Updated: 2021/06/04 00:10:25 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk_bonus.h"

int		g_original;
int		g_count;
int		g_num;
char	g_save[1024];
int		g_index;

struct sigaction act1;
struct sigaction act2;

void	make_count0(int signum, siginfo_t *info, void *v)
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
			kill(info->si_pid, SIGUSR1);
		}
		g_original = 0;
	}
	sigaction(SIGUSR2, &act2, NULL);
}

void	make_count1(int signum, siginfo_t *info, void *v)
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
			kill(info->si_pid, SIGUSR1);
		}
		g_original = 0;
	}
	sigaction(SIGUSR1, &act1, NULL);
}

void	resend_signal(void)
{
	act1.sa_flags = SIGINFO;
	act2.sa_flags = SIGINFO;
	act1.__sigaction_u.__sa_sigaction = make_count1;
	act2.__sigaction_u.__sa_sigaction = make_count0;
	sigaction(SIGUSR1, &act1, NULL);
	sigaction(SIGUSR2, &act2, NULL);
}

int		main(void)
{
	int pid;

	g_count = 7;
	pid = getpid();
	g_original = 0;
	ft_putnbr_fd(pid, 1);
	write(1, "\n", 1);
	resend_signal();
	while (1)
		;
}
