/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 22:46:26 by seungyel          #+#    #+#             */
/*   Updated: 2021/03/21 23:12:30 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_p_type_2(int j, char *out)
{
	int			gap;

	out[j + 2] = '\0';
	gap = g_flag.min_width - j - 2;
	j = 0;
	while (g_flag.flag_minus != 1 && gap-- > 0)
		ft_putchar(' ');
	while (out[j])
		ft_putchar(out[j++]);
	while (g_flag.flag_minus == 1 && gap-- > 0)
		ft_putchar(' ');
}

void	ft_p_type_1(va_list ap, int i, int j, int index)
{
	char		out[20];
	char		out_reverse[13];
	long long	num;

	num = (long long)va_arg(ap, void *);
	while (num >= 16)
	{
		out_reverse[i++] = "0123456789abcdef"[num % 16];
		num /= 16;
	}
	out_reverse[i] = "0123456789abcdef"[num];
	index = i;
	out[0] = '0';
	out[1] = 'x';
	if (g_flag.flag_precision == 1 && g_flag.precision == 0 && num == 0)
		out[2] = '\0';
	else
	{
		while (j + 2 <= index + 2)
		{
			out[j + 2] = out_reverse[i--];
			j++;
		}
	}
	ft_p_type_2(j, out);
}
