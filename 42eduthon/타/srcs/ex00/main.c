/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 10:42:21 by chanhpar          #+#    #+#             */
/*   Updated: 2022/08/24 14:13:05 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

extern void	eleven_number_checker(char *input);
extern void	check_leaks(void);

int	main(void)
{
	atexit(check_leaks);
	eleven_number_checker("");
	eleven_number_checker(NULL);
	eleven_number_checker("01012345678");
	eleven_number_checker("0101234o678");
	eleven_number_checker(" 01012345678");
	eleven_number_checker("01012345678 ");
	eleven_number_checker(" 01012345678 ");
	eleven_number_checker("010 1 2 3 4 5 6 7 8");
	eleven_number_checker("12345678901a");
	eleven_number_checker("01011112222");
	eleven_number_checker("01022221111");
	eleven_number_checker("01022221111 ");
	eleven_number_checker("01000000000");
	eleven_number_checker("aaa01011111111aaa");
	eleven_number_checker("aaa01022222222222");
	eleven_number_checker("   01033333333   ");
	eleven_number_checker("01044A44444");
	eleven_number_checker("01055 55555");
	eleven_number_checker("01066_66666");
	eleven_number_checker("01042424242");
	eleven_number_checker("aaa01042424242aaa");
	eleven_number_checker("aaa010424242424253");
	eleven_number_checker("   0104242424242   ");
	eleven_number_checker("01042A24242");
	eleven_number_checker("01042 24242");
	eleven_number_checker("01042_24242");
	eleven_number_checker("01042A424242");
	eleven_number_checker("01042 42424");
	eleven_number_checker("01042424242");
	eleven_number_checker("010424242424");
	eleven_number_checker("01042424242  ");
	eleven_number_checker("   01042424242");
	eleven_number_checker("   01042424242   ");
	eleven_number_checker("01042  424242");
	return (0);
}
