/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 10:42:32 by chanhpar          #+#    #+#             */
/*   Updated: 2022/08/24 14:20:20 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

extern void	simple_password_validator(const char *input);
extern void	check_leaks(void);

int	main(void)
{
	atexit(check_leaks);
	simple_password_validator((void *)0);
	simple_password_validator("");
	simple_password_validator("banana31@");
	simple_password_validator("banana31.");
	simple_password_validator("apple31@");
	simple_password_validator("banana42@");
	simple_password_validator("banana31 @");
	simple_password_validator("banana31@@@@@");
	simple_password_validator("  banana31@  ");
	simple_password_validator(".banana31@");
	return (0);
}
