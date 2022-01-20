/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeukim <byeukim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:15:31 by byeukim           #+#    #+#             */
/*   Updated: 2021/12/02 12:15:33 by byeukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	find_cmd(char *env, char *command)
{
	int	equ;

	equ = -1;
	while (env[++equ] != '=')
		;
	if (!ft_strncmp(env, command, equ))
		return (1);
	return (0);
}

int	ft_unset(char **command, t_info *info)
{
	char	**edit_env;
	int		i;
	int		j;

	i = -1;
	j = -1;
	edit_env = malloc(sizeof(char *) * info->env_size + 1);
	if (!edit_env)
		return (0);
	while (info->env[++i])
	{
		if (find_cmd(info->env[i], command[1]))
			info->env_size -= 1;
		else
		{
			edit_env[++j] = ft_strdup(info->env[i]);
			if (!edit_env[j] && !free_matrix(&edit_env))
				return (0);
		}
	}
	edit_env[j + 1] = free_matrix(&(info->env));
	info->env = edit_env;
	return (1);
}
