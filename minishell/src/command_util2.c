/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_util2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeukim <byeukim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:14:47 by byeukim           #+#    #+#             */
/*   Updated: 2021/12/02 12:14:50 by byeukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	space_count(char *command)
{
	int		idx;
	int		count;
	int		flag;

	idx = -1;
	count = 1;
	flag = 0;
	while (command[++idx])
	{
		if (!flag && command[idx] == '"')
		{
			flag = 1;
			continue ;
		}
		else if (flag && command[idx] == '"')
		{
			flag = 0;
			continue ;
		}
		else if (flag)
			continue ;
		if (command[idx] == ' ' && (idx > 0 && command[idx - 1] != ' '))
			count += 1;
	}
	return (count);
}

char	*add_word(char **result, char word)
{
	char	*new;
	int		len;
	int		idx;

	if (!(*result))
		len = 0;
	else
		len = ft_strlen(*result);
	new = malloc(sizeof(char) * (len + 2));
	if (!new)
		return (NULL);
	idx = 0;
	while ((*result) && (*result)[idx])
	{
		new[idx] = (*result)[idx];
		idx++;
	}
	new[idx] = word;
	new[idx + 1] = 0;
	free(*result);
	return (new);
}

char	*conv_dallor(char *result, char *command, int len, t_info *info)
{
	char	*env_element;
	char	*key;
	char	*temp;

	key = ft_strndup(command, len);
	env_element = find_env_value(info, key);
	if (!env_element)
		env_element = ft_strdup("");
	if (!result)
		result = ft_strdup(env_element);
	else
	{
		temp = ft_strjoin(result, env_element);
		free(result);
		result = temp;
	}
	if (key)
		free(key);
	free(env_element);
	return (result);
}

int	check_save_word(char word, char **result)
{
	static int	flag;

	if (word == '"')
		return (1);
	else if (!flag && word == '\'')
		flag = 1;
	else if (flag && word == '\'')
		flag = 0;
	else if (!flag && word == '$')
		return (0);
	else
	{
		*result = add_word(result, word);
		if (!(*result))
			return (0);
	}
	return (1);
}
