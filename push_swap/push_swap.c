/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                            =        +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 13:49:57 by seungyel          #+#    #+#             */
/*   Updated: 2021/07/09 14:06:15 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <stdio.h>

int	main(int argc, char *argv[])
{
	t_push_swap	data;

	if (argc < 2)
		return (0);
	ft_memset(&data, 0, sizeof(data));
	data.visualizer = OP;
	data.a = create_stack_with_arg(argc, argv);
	data.b = NULL;
	
	return (0);
}