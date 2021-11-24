/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seungyel <seungyel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 20:00:43 by seungyel          #+#    #+#             */
/*   Updated: 2021/03/21 23:16:10 by seungyel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

typedef	struct		s_flag
{
	int				flag_minus;
	int				flag_zero;
	int				flag_precision;
	int				precision;
	int				min_width;
	int				char_count;
}					t_flag;
typedef struct		s_d_vars
{
	int				zero_remains;
	int				num_len;
	long long		num;
	unsigned int	u_num;
	unsigned int	x_num;
	int				is_negative;
	char			symbol_of_padding;
	char			*str_of_num;
}					t_d_vars;
t_flag	g_flag;
void				ft_c_type(va_list ap);
void				ft_s_type_1(va_list ap);
void				ft_s_type_2(char *type, int argument_len, int gap);
void				ft_percent_type(void);
void				ft_minus_zero_check(const char **format);
void				ft_putchar(char c);
void				ft_type_check(const char **format, va_list ap);
void				ft_d_type(va_list ap, t_d_vars var);
void				d_minus_flag(t_d_vars var);
void				d_no_minus_flag(t_d_vars var);
void				ft_p_type_1(va_list ap, int i, int j, int index);
void				ft_p_type_2(int j, char *out);
void				u_no_minus_flag(t_d_vars var);
void				u_minus_flag(t_d_vars var);
void				ft_u_type(va_list ap, t_d_vars var);
void				ft_x_type(va_list ap, char type);
int					ft_printf(const char *format, ...);
int					ft_precision(const char **format, va_list ap);
int					ft_isdigit(int c);
int					ft_min_width(const char **format, va_list ap);
char				*ft_itoa_hex(long long n, char type);
char				*ft_itoa(long long n);
size_t				ft_strlen(const char *str);
char				*ft_strchr(char *str, int c);
#endif
