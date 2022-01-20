/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:45:39 by seungyel          #+#    #+#             */
/*   Updated: 2021/12/01 15:45:46 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	move_dir(char *cmd, char **cur_path)
{
	DIR				*dir;
	struct dirent	*ent;
	char			*temp;

	dir = opendir(*cur_path);
	if (!dir)
		return (0);
	ent = readdir(dir);
	while (ent)
	{
		if (!ft_strcmp(ent->d_name, cmd))
		{
			temp = ft_strjointri(*cur_path, "/", cmd);
			chdir(temp);
			free(temp);
			*cur_path = getcwd(NULL, BUFSIZ);
			closedir(dir);
			return (1);
		}
		ent = readdir(dir);
	}
	return (0);
}

int	move_base(char **command, t_info *info)
{
	if (command[1][0] == '/')
		chdir("/");
	else if (command[1][0] == '~')
		chdir(info->home);
	else if (command[1][0] == '-')
	{
		if (!info->oldpwd)
		{
			printf("minishell: cd: OLDPWD not set\n");
			return (0);
		}
		chdir(info->oldpwd);
	}
	return (1);
}

int	ft_cd(char **command, t_info *info)
{
	int		idx;
	char	**split_cmd;
	char	*cur_path;

	idx = -1;
	if (!move_base(command, info))
		return (0);
	split_cmd = ft_split(command[1], '/');
	cur_path = getcwd(NULL, BUFSIZ);
	info->oldpwd = info->pwd;
	while (split_cmd[++idx] && split_cmd[idx][0] != '~' \
	&& split_cmd[idx][0] != '-')
	{
		if (!move_dir(split_cmd[idx], &cur_path))
		{
			free_matrix(&split_cmd);
			return (0);
		}
	}
	free_matrix(&split_cmd);
	info->pwd = NULL;
	info->pwd = getcwd(NULL, BUFSIZ);
	return (1);
}
