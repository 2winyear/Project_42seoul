/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeukim <byeukim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:15:56 by byeukim           #+#    #+#             */
/*   Updated: 2021/12/02 12:15:57 by byeukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (TRUE);
	return (FALSE);
}

int	ft_strlen(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		;
	return (i);
}

int	ft_atoi(char *str)
{
	int	num;
	int	idx;

	num = 0;
	idx = -1;
	if (!str)
		return (FALSE);
	while (str[++idx])
	{
		if (!ft_isdigit(str[idx]))
			return (FALSE);
	}
	while (idx > 0)
		num = (num * 10) + '0' - str[--idx];
	return (num);
}

int	ft_nbrlen(int num)
{
	int	len;

	len = 0;
	while (num)
	{
		num /= 10;
		len++;
	}
	return (len);
}
