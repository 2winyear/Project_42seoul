/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstclear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <lsy2246@naver.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 11:41:13 by seungyel          #+#    #+#             */
/*   Updated: 2020/11/26 12:58:12 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*to_free;

	if (!*lst)
		return ;
	while (*lst != NULL)
	{
		del((*lst)->content);
		to_free = *lst;
		(*lst) = (*lst)->next;
		free(to_free);
	}
}
