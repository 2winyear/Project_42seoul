/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 10:42:39 by chanhpar          #+#    #+#             */
/*   Updated: 2022/08/24 14:14:33 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

extern void	push_swap_instruction_validator(char *input);
extern void	check_leaks(void);

int	main(void)
{
	atexit(check_leaks);
	push_swap_instruction_validator(NULL);
	push_swap_instruction_validator("");
	push_swap_instruction_validator("sa");
	push_swap_instruction_validator("sb");
	push_swap_instruction_validator("ss");
	push_swap_instruction_validator("pa");
	push_swap_instruction_validator("pb");
	push_swap_instruction_validator("ra");
	push_swap_instruction_validator("rb");
	push_swap_instruction_validator("rr");
	push_swap_instruction_validator("rra");
	push_swap_instruction_validator("rrb");
	push_swap_instruction_validator("pbpa");
	push_swap_instruction_validator("rrr");
	push_swap_instruction_validator("rrrrrr");
	push_swap_instruction_validator("    sa");
	push_swap_instruction_validator("sa  ");
	push_swap_instruction_validator("    sa  ");
	push_swap_instruction_validator("pp");
	push_swap_instruction_validator("aa");
	push_swap_instruction_validator("aaa");
	push_swap_instruction_validator("sr");
	push_swap_instruction_validator("SR");
	push_swap_instruction_validator("s@");
	push_swap_instruction_validator("@a");
	push_swap_instruction_validator("1a");
	return (0);
}
