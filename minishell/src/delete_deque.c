/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_deque.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: byeukim <byeukim@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 12:14:53 by byeukim           #+#    #+#             */
/*   Updated: 2021/12/02 12:14:54 by byeukim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	delete_deque(t_deque **cmd)
{
	t_deque_node	*curr_node;
	t_deque_node	*prev_node;
	int				idx;

	if (!(*cmd))
		return ;
	prev_node = &((*cmd)->tailer_node);
	curr_node = prev_node->prev_node;
	while (curr_node != &((*cmd)->header_node))
	{
		prev_node = curr_node;
		curr_node = prev_node->prev_node;
		delete_deque_node(&(prev_node));
	}
	idx = -1;
	while ((*cmd)->seperates[++idx])
		free((*cmd)->seperates[idx]);
	free((*cmd)->seperates);
	free(*cmd);
	*cmd = NULL;
}

void	delete_deque_node(t_deque_node **node)
{
	int	idx;

	idx = -1;
	while ((*node)->command[++idx])
		free((*node)->command[idx]);
	free((*node)->command);
	if ((*node)->seperate)
		free((*node)->seperate);
	free(*node);
	*node = NULL;
}
