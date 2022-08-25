/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 10:42:48 by chanhpar          #+#    #+#             */
/*   Updated: 2022/08/24 14:29:26 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

extern void	snake_to_camel(char *input);
extern void	check_leaks(void);

int	main(void)
{
	atexit(check_leaks);
	snake_to_camel("");
	snake_to_camel(NULL);
	snake_to_camel("hello");
	snake_to_camel("hello_");
	snake_to_camel("_hello");
	snake_to_camel("_hello_");
	snake_to_camel("world_hello");
	snake_to_camel("world_hello  ");
	snake_to_camel(" world_hello");
	snake_to_camel("World_hello");
	snake_to_camel("worLd_hello");
	snake_to_camel("world__hello");
	snake_to_camel("foo_bar  world_hello");
	snake_to_camel("_");
	snake_to_camel("a_B");
	snake_to_camel("a_bc_def_ghi");
	snake_to_camel("worl d_hello");
	snake_to_camel("world_Hello");
	snake_to_camel("world_hello\n");
	snake_to_camel("42_Hello");
	snake_to_camel("world()_hi");
	return (0);
}
