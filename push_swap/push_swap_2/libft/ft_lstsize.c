/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jae-kim <jae-kim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 00:38:40 by jae-kim           #+#    #+#             */
/*   Updated: 2021/01/06 00:39:21 by jae-kim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*ptr;

	if (lst == NULL)
		return (0);
	i = 1;
	ptr = lst;
	while (ptr->next)
	{
		ptr = ptr->next;
		i++;
	}
	return (i);
}
