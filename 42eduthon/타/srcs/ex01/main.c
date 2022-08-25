/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chanhpar <chanhpar@student.42seoul.kr      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 10:42:25 by chanhpar          #+#    #+#             */
/*   Updated: 2022/08/24 14:15:51 by chanhpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

extern void	phone_number_checker(const char *input);
extern void	check_leaks(void);

int	main(void)
{
	atexit(check_leaks);
	phone_number_checker(NULL);
	phone_number_checker("");
	phone_number_checker("010-1234-5678");
	phone_number_checker("010-12a4-5678");
	phone_number_checker("010-1234-5678   010-888-7777");
	phone_number_checker("000-0000-0000");
	phone_number_checker("010-0000-0000");
	phone_number_checker("0100000-0000");
	phone_number_checker("010-111-1111");
	phone_number_checker("010-2222-2222010-2222-2222");
	phone_number_checker("010-3333-3333   010-3333-3333");
	phone_number_checker("010-4444-4444   010-4444-4A44");
	phone_number_checker("   010-555-5555   010-5555-5555  ");
	phone_number_checker("abc010-6666-6666defg010-6666-6666hijkl");
	phone_number_checker("010-7777-7010-7777-7777");
	phone_number_checker("010-1234-567");
	phone_number_checker("010-123-567");
	phone_number_checker("0101234-5678");
	phone_number_checker("010-12345678");
	phone_number_checker("010-1234a5678");
	phone_number_checker("010-1234 5678");
	phone_number_checker("010-1234-5678");
	phone_number_checker("010-123-5678");
	phone_number_checker("010-4242-4242010-9999-8888");
	phone_number_checker("010-4242-4242   010-5353-5353");
	phone_number_checker("010-4242-4242   010-5353-5A53");
	phone_number_checker("010-4242-4242   010-5353-5 53");
	phone_number_checker("010-4242-4242   010-5353-5_53");
	phone_number_checker("   010-4242-4242   010-2424-2424  ");
	phone_number_checker("abc010-4242-4242defg010-2424-2424hijkl");
	phone_number_checker("010-1234-5010-4242-4242");
	return (0);
}
