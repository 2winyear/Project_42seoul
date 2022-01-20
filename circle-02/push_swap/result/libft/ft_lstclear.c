/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 22:30:17 by jae-kim           #+#    #+#             */
/*   Updated: 2021/10/05 11:13:28 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void
*))
{
	t_list	*ptr;

	if (del == 0)
		return ;
	while (*lst)
	{
		ptr = (*lst)->next;
		del((*lst)->content);
		(*lst)->next = NULL;
		free(*lst);
		(*lst) = ptr;
	}
	lst = NULL;
	free(lst);
}
