/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <lsy2246@naver.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 12:36:48 by seungyel          #+#    #+#             */
/*   Updated: 2020/11/27 10:37:27 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f) (void *))
{
	t_list *cursor;

	cursor = lst;
	if (lst == NULL || f == NULL)
		return ;
	while (cursor != NULL)
	{
		(*f)(cursor->content);
		cursor = cursor->next;
	}
}
