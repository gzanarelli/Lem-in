/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_flagssize.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/04 18:41:06 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/04 19:28:28 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_flags(t_flags *flags)
{
	flags->minus = 0;
	flags->plus = 0;
	flags->zero = 0;
	flags->space = 0;
	flags->sharp = 0;
}

int		parse_flags(const char *format, t_flags *flags)
{
	int i;

	init_flags(flags);
	i = 0;
	while (*format == '-' || *format == '+' || *format == '0'
			|| *format == ' ' || *format == '#')
	{
		if (*format == '-')
			flags->minus = 1;
		else if (*format == '+')
			flags->plus = 1;
		else if (*format == '0')
			flags->zero = 1;
		else if (*format == ' ')
			flags->space = 1;
		else if (*format == '#')
			flags->sharp = 1;
		format++;
		i++;
	}
	if (flags->zero && flags->minus)
		flags->zero = 0;
	return (i);
}

void	init_size(t_argsz *argsz)
{
	argsz->hh = 0;
	argsz->h = 0;
	argsz->l = 0;
	argsz->ll = 0;
	argsz->j = 0;
	argsz->t = 0;
	argsz->z = 0;
	argsz->ul = 0;
}

int		get_argsize(const char *format, t_argsz *argsz, int i)
{
	i = 0;
	if (*format == 'h' && *(format + 1) == 'h')
	{
		argsz->hh = 1;
		i += 2;
	}
	else if (*format == 'h' && ++i)
		argsz->h = 1;
	else if (*format == 'l' && *(format + 1) == 'l')
	{
		argsz->ll = 1;
		i += 2;
	}
	else if (*format == 'l' && ++i)
		argsz->l = 1;
	else if (*format == 'j' && ++i)
		argsz->j = 1;
	else if (*format == 't' && ++i)
		argsz->t = 1;
	else if (*format == 'z' && ++i)
		argsz->z = 1;
	else if (*format == 'L' && ++i)
		argsz->ul = 1;
	return (i);
}

int		parse_size(const char *format, t_argsz *argsz)
{
	int i;

	i = 0;
	init_size(argsz);
	i = get_argsize(format, argsz, i);
	if (i)
		format++;
	return (i);
}
