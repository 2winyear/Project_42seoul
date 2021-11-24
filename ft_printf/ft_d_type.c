/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_d_type.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 22:58:07 by seungyel          #+#    #+#             */
/*   Updated: 2021/03/21 22:58:26 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	d_no_minus_flag(t_d_vars var)
{
	int padding_size;

	if (g_flag.precision < var.num_len)
		padding_size = g_flag.min_width - var.num_len - var.is_negative;
	else
		padding_size = g_flag.min_width - g_flag.precision - var.is_negative;
	if (g_flag.flag_precision == 1 && g_flag.precision == 0 && var.num == 0)
	{
		if (padding_size > -1)
			padding_size++;
		var.num_len = 0;
	}
	if (g_flag.flag_zero == 1 && g_flag.flag_precision == 0 && var.is_negative)
		ft_putchar('-');
	while (padding_size-- > 0)
		ft_putchar(var.symbol_of_padding);
	if (g_flag.flag_zero == 0 && g_flag.flag_precision == 0 && var.is_negative)
		ft_putchar('-');
	if (g_flag.flag_precision == 1 && var.is_negative)
		ft_putchar('-');
	var.zero_remains = g_flag.precision - var.num_len;
	while (var.zero_remains-- > 0)
		ft_putchar('0');
	while ((var.num_len)--)
		ft_putchar(*(var.str_of_num)++);
}

void	d_minus_flag(t_d_vars var)
{
	int padding_size;

	if (var.is_negative == 1)
		ft_putchar('-');
	if (g_flag.precision < var.num_len)
		padding_size = g_flag.min_width - var.num_len - var.is_negative;
	else
		padding_size = g_flag.min_width - g_flag.precision - var.is_negative;
	var.zero_remains = g_flag.precision - var.num_len;
	while (var.zero_remains-- > 0)
		ft_putchar('0');
	while ((var.num_len)--)
	{
		if (g_flag.flag_precision == 1 && g_flag.precision == 0
			&& var.num == 0)
		{
			if (padding_size > -1)
				padding_size++;
			var.num_len = 0;
		}
		else
			ft_putchar(*(var.str_of_num)++);
	}
	while (padding_size-- > 0)
		ft_putchar(var.symbol_of_padding);
}

void	ft_d_type(va_list ap, t_d_vars var)
{
	var.num = va_arg(ap, int);
	if (g_flag.flag_zero == 1)
	{
		var.symbol_of_padding = '0';
		if (g_flag.flag_minus == 1 || g_flag.flag_precision == 1
			|| g_flag.precision < 0)
			var.symbol_of_padding = ' ';
	}
	else
		var.symbol_of_padding = ' ';
	if (var.num < 0)
	{
		var.num *= (-1);
		var.is_negative = 1;
	}
	var.str_of_num = ft_itoa(var.num);
	if (!var.str_of_num)
		return ;
	var.num_len = ft_strlen(var.str_of_num);
	if (g_flag.flag_minus == 0)
		d_no_minus_flag(var);
	else
		d_minus_flag(var);
	free(var.str_of_num);
}
