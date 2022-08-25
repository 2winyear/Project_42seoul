/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_leaks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 10:48:48 by chanhpar          #+#    #+#             */
/*   Updated: 2022/08/24 10:48:49 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	check_leaks(void)
{
	system("leaks --quiet $PPID > /dev/null ; echo leaks: $?");
}
