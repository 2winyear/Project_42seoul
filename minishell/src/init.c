/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeukim <byeukim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:15:36 by byeukim           #+#    #+#             */
/*   Updated: 2021/12/02 12:15:36 by byeukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	display_logo(t_info *info)
{
	int		fd;
	int		bytes;
	char	buf[BUF_SIZE];
	char	*path;

	path = ft_strjointri(info->pwd, "/src/", "front_logo");
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return ;
	bytes = read(fd, buf, BUF_SIZE - 1);
	buf[bytes] = '\0';
	if (bytes == -1)
	{
		close(fd);
		return ;
	}
	printf("%s", buf);
	close(fd);
	free(path);
}

void	*free_info(t_info **info)
{
	int	idx;

	idx = -1;
	if ((*info)->cmd)
		delete_deque(&((*info)->cmd));
	if ((*info)->env)
	{
		while ((*info)->env[++idx])
		{
			free((*info)->env[idx]);
			(*info)->env[idx] = NULL;
		}
		free((*info)->env);
		(*info)->env = NULL;
	}
	if ((*info)->pwd)
		free((*info)->pwd);
	free(*info);
	*info = NULL;
	return (NULL);
}

t_info	*init_info(char **env)
{
	t_info	*info;
	int		idx;

	info = malloc(sizeof(t_info));
	if (!info)
		return (NULL);
	info->env = env_dup(env, 0, NULL);
	if (!info->env)
		return (free_info(&info));
	idx = -1;
	while (env[++idx])
	{
		if (!ft_strncmp(env[idx], "HOME", 4))
			info->home = env[idx] + 5;
	}
	info->pwd = getcwd(NULL, BUF_SIZE);
	info->oldpwd = NULL;
	info->env_size = idx;
	info->status = 0;
	return (info);
}
