/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 19:52:41 by seungyel          #+#    #+#             */
/*   Updated: 2021/03/21 23:00:58 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_minus_zero_check(const char **format)
{
	g_flag.flag_zero = 0;
	g_flag.flag_minus = 0;
	while (**format == '-' || **format == '0')
	{
		if (**format == '-')
			g_flag.flag_minus = 1;
		else if (**format == '0')
			g_flag.flag_zero = 1;
		++(*format);
	}
}

int		ft_min_width(const char **format, va_list ap)
{
	int min_width;

	min_width = 0;
	if (**format == '*')
	{
		min_width = va_arg(ap, int);
		++(*format);
		if (min_width < 0)
		{
			g_flag.flag_minus = 1;
			min_width *= -1;
		}
	}
	while (ft_isdigit(**format) == 1)
	{
		min_width = min_width * 10 + (**format - '0');
		++(*format);
	}
	return (min_width);
}

int		ft_precision(const char **format, va_list ap)
{
	int	precision;

	precision = 0;
	g_flag.flag_precision = 0;
	if (**format == '.')
	{
		g_flag.flag_precision = 1;
		++(*format);
		if (**format == '*')
		{
			precision = va_arg(ap, int);
			if (precision < 0)
			{
				precision = 0;
				g_flag.flag_precision = 0;
			}
			++(*format);
		}
		while (ft_isdigit(**format) == 1)
		{
			precision = precision * 10 + (**format - '0');
			++(*format);
		}
	}
	return (precision);
}

void	ft_type_check(const char **format, va_list ap)
{
	t_d_vars	var;

	var.zero_remains = 0;
	var.is_negative = 0;
	if (**format == 'd' || **format == 'i')
		ft_d_type(ap, var);
	else if (**format == 'u')
		ft_u_type(ap, var);
	else if (**format == 'x')
		ft_x_type(ap, 'x');
	else if (**format == 'X')
		ft_x_type(ap, 'X');
	else if (**format == 'p')
		ft_p_type_1(ap, 0, 0, 0);
	else if (**format == 'c')
		ft_c_type(ap);
	else if (**format == 's')
		ft_s_type_1(ap);
	else if (**format == '%')
		ft_percent_type();
	++(*format);
}

int		ft_printf(const char *format, ...)
{
	va_list	ap;

	g_flag.char_count = 0;
	va_start(ap, format);
	if (format == NULL)
		return (0);
	while (*format)
	{
		if (*format++ == '%')
		{
			ft_minus_zero_check(&format);
			g_flag.min_width = ft_min_width(&format, ap);
			g_flag.precision = ft_precision(&format, ap);
			ft_type_check(&format, ap);
		}
		else
			ft_putchar(*(format - 1));
	}
	va_end(ap);
	return (g_flag.char_count);
}
