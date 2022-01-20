/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_u_x_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 22:59:44 by seungyel          #+#    #+#             */
/*   Updated: 2021/03/21 23:00:04 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	u_no_minus_flag(t_d_vars var)
{
	int	padding_size;

	if (g_flag.precision < var.num_len)
		padding_size = g_flag.min_width - var.num_len;
	else
		padding_size = g_flag.min_width - g_flag.precision;
	if (g_flag.flag_precision == 1 && g_flag.precision == 0
			&& var.u_num == 0)
	{
		if (padding_size > -1)
			padding_size++;
		var.num_len = 0;
	}
	while (padding_size-- > 0)
		ft_putchar(var.symbol_of_padding);
	var.zero_remains = g_flag.precision - var.num_len;
	while (var.zero_remains-- > 0)
		ft_putchar('0');
	while ((var.num_len)--)
		ft_putchar(*(var.str_of_num)++);
}

void	u_minus_flag(t_d_vars var)
{
	int padding_size;

	if (g_flag.precision < var.num_len)
		padding_size = g_flag.min_width - var.num_len;
	else
		padding_size = g_flag.min_width - g_flag.precision;
	var.zero_remains = g_flag.precision - var.num_len;
	while (var.zero_remains-- > 0)
		ft_putchar('0');
	while ((var.num_len)-- > 0)
	{
		if (g_flag.flag_precision == 1
		&& g_flag.precision == 0 && var.u_num == 0)
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

void	ft_u_type(va_list ap, t_d_vars var)
{
	var.zero_remains = 0;
	var.u_num = va_arg(ap, unsigned int);
	var.str_of_num = ft_itoa(var.u_num);
	if (g_flag.flag_zero == 1)
	{
		var.symbol_of_padding = '0';
		if (g_flag.flag_minus == 1 || g_flag.flag_precision == 1
			|| g_flag.precision < 0)
			var.symbol_of_padding = ' ';
	}
	else
		var.symbol_of_padding = ' ';
	if (g_flag.flag_precision == 1 && g_flag.precision == 0
			&& var.u_num == 0)
	{
		var.symbol_of_padding = ' ';
	}
	if (!var.str_of_num)
		return ;
	var.num_len = ft_strlen(var.str_of_num);
	if (g_flag.flag_minus == 0)
		u_no_minus_flag(var);
	else
		u_minus_flag(var);
	free(var.str_of_num);
}

void	ft_x_type(va_list ap, char type)
{
	t_d_vars	var;

	var.zero_remains = 0;
	var.u_num = va_arg(ap, unsigned int);
	if (g_flag.flag_zero)
	{
		var.symbol_of_padding = '0';
		if (g_flag.flag_minus == 1)
			var.symbol_of_padding = ' ';
		if (g_flag.flag_precision == 1 || g_flag.precision < 0)
			var.symbol_of_padding = ' ';
	}
	else
		var.symbol_of_padding = ' ';
	if (g_flag.flag_precision == 1 && g_flag.precision == 0 && var.u_num == 0)
		var.symbol_of_padding = ' ';
	var.str_of_num = ft_itoa_hex(var.u_num, type);
	if (!var.str_of_num)
		return ;
	var.num_len = ft_strlen(var.str_of_num);
	if (g_flag.flag_minus == 0)
		u_no_minus_flag(var);
	else
		u_minus_flag(var);
	free(var.str_of_num);
}
