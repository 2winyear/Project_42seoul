/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kim <jae-kim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/04 22:43:56 by jae-kim           #+#    #+#             */
/*   Updated: 2021/01/06 15:05:05 by jae-kim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *),
void (*del)(void *))
{
	t_list *new_lst;
	t_list *ret;

	if (!lst)
		return (NULL);
	if (!(new_lst = ft_lstnew(f(lst->content))))
		return (NULL);
	ret = new_lst;
	lst = lst->next;
	while (lst)
	{
		if (!(new_lst->next = ft_lstnew(f(lst->content))))
		{
			while (ret)
			{
				ft_lstclear(&ret, del);
				ret = ret->next;
			}
			return (NULL);
		}
		new_lst = new_lst->next;
		lst = lst->next;
	}
	return (ret);
}
