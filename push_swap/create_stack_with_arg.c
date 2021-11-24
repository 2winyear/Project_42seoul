/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_stack_with_arg.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 09:06:29 by seungyel          #+#    #+#             */
/*   Updated: 2021/09/11 00:10:15 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static long atoi_check

t_stack* create_stack_with_arg(int argc, char *argv[])
{
	int iv[2];
	char **split;
	t_stack *result;
	t_stack *tmp;

	result = NULL;
	iv[0] = NULL;
	while (++iv[0] < argc)
	{
		split = ft_split(argv[iv[0]], ' ');
		if (split == NULL)
			put_error_with_clear(result, split);
		iv[1] = -1;
        while (split[++iv[1]])
        {
            tmp = stack_new(atoi_check(split[iv[1]], result, split));
            if (tmp == NULL)
                put_error_with_clear(result, split);
            stack_add_back(&result, tmp);
        }
        ft_split_clean(split);
	}
    return (result);
}