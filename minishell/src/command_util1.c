/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_util1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeukim <byeukim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:14:36 by byeukim           #+#    #+#             */
/*   Updated: 2021/12/02 12:14:37 by byeukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*find_conv_dallor(char *command, t_info *info)
{
	char	*result;
	int		start;
	int		len;

	start = -1;
	result = NULL;
	while (command[++start])
	{
		len = 0;
		if (check_save_word(command[start], &result))
			continue ;
		else if (command[start] == '$')
		{
			while (command[++start] && (command[start] != ' ' \
						&& command[start] != '"'))
				len += 1;
			result = conv_dallor(result, command + start - len, len, info);
			start -= 1;
		}
		else
			return (NULL);
	}
	free(command);
	return (result);
}

char	*div_dup(char *command, t_info *info)
{
	char	*temp;
	int		idx;
	int		flag;

	temp = NULL;
	idx = -1;
	flag = 0;
	while (command[++idx])
	{
		if (!flag && command[idx] == '"')
			flag = 1;
		else if (flag && command[idx] == '"')
			flag = 0;
		else if (!flag && command[idx] == ' ')
		{
			temp = ft_strndup(command, idx);
			break ;
		}
	}
	if (!command[idx])
		temp = ft_strndup(command, idx);
	if (!temp)
		return (NULL);
	return (find_conv_dallor(temp, info));
}

int	check_flag_space(char *command, int *start, int *prev_start)
{
	static int	flag;

	if (!flag && command[*start] == '"')
		flag = 1;
	else if (flag && command[*start] == '"')
		flag = 0;
	else if (flag)
		;
	else if (command[*start] == ' ')
	{
		if (*start > 0 && command[*start - 1] != ' ')
			return (1);
		while (command[*start] && command[*start] == ' ')
		{
			(*start)++;
			(*prev_start)++;
		}
		return (0);
	}
	return (0);
}

char	**set_split_cmd(t_info *info, char *command)
{
	char	**result;
	int		start;
	int		prev_start;
	int		idx;

	start = -1;
	prev_start = 0;
	idx = -1;
	result = malloc(sizeof(char *) * (space_count(command) + 1));
	if (!result)
		return (NULL);
	while (command[++start])
	{
		if (check_flag_space(command, &start, &prev_start) \
				|| !command[start + 1])
		{
			result[++idx] = div_dup(command + prev_start, info);
			if (!result[idx])
				return (free_matrix(&result));
			prev_start = start + 1;
		}
	}
	result[idx + 1] = NULL;
	return (result);
}

int	save_command(t_info *info, char *command, int spt_type, int len)
{
	char			**split_cmd;
	char			*temp_spr;
	char			*temp;
	t_deque_node	*new_node;

	temp = ft_strndup(command, len);
	if (!temp)
		return (0);
	split_cmd = set_split_cmd(info, temp);
	free(temp);
	if (!split_cmd)
		return (0);
	if (spt_type != -1)
		temp_spr = ft_strdup(info->cmd->seperates[spt_type]);
	else
		temp_spr = NULL;
	new_node = make_deque_node(split_cmd, temp_spr, spt_type);
	if (!new_node)
		return (0);
	push_deque(info->cmd, new_node);
	return (1);
}
