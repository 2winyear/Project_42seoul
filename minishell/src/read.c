/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeukim <byeukim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:15:49 by byeukim           #+#    #+#             */
/*   Updated: 2021/12/02 12:44:58 by byeukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sig_handler(int signum)
{
	extern void	rl_replace_line(const char *text, int n);

	if (signum == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	return ;
}

void	init_signal(void)
{
	signal(SIGINT, (void *)sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

char	*read_line(t_info *info)
{
	char		*str;
	char		*prompt;
	extern int	rl_catch_signals;
	extern int	rl_point;

	init_signal();
	prompt = ft_strjoin(info->pwd, "  ▶ ");
	if (!prompt)
		exit(1);
	rl_catch_signals = 0;
	if (!rl_point)
		printf("\033[500D");
	str = readline(prompt);
	free(prompt);
	if (!str)
	{
		printf("exit\n");
		exit(4);
	}
	else if (str)
	{
		if (strlen(str))
			add_history(str);
	}
	return (str);
}
