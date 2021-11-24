/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <lsy2246@naver.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 16:17:52 by seungyel          #+#    #+#             */
/*   Updated: 2020/12/02 12:00:02 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*d)(void *))
{
	t_list	*newlst;
	t_list	*temp;
	t_list	*curr;

	if (lst == 0)
		return (NULL);
	if ((newlst = ft_lstnew(f(lst->content))) == 0)
		return (NULL);
	curr = newlst;
	lst = lst->next;
	while (lst)
	{
		if ((temp = ft_lstnew(f(lst->content))) == 0)
		{
			ft_lstclear(&newlst, d);
			return (NULL);
		}
		curr->next = temp;
		curr = temp;
		lst = lst->next;
	}
	return (newlst);
}
