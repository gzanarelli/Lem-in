/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_precwidth.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/04 18:38:39 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/04 18:39:08 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		parse_width(const char *format, t_parse *parse)
{
	int i;

	parse->width = -1;
	i = 0;
	if (*format == '*')
	{
		format++;
		i++;
	}
	else if (*format >= '0' && *format <= '9')
	{
		parse->width = ft_atoi(format);
		while (*format >= '0' && *format <= '9')
		{
			format++;
			i++;
		}
	}
	return (i);
}

int		parse_precision(const char *format, t_parse *parse)
{
	int i;

	parse->precision = -1;
	i = 0;
	if (*format == '.')
	{
		parse->precision = 0;
		format++;
		i++;
		if (*format == '*')
		{
			format++;
			i++;
		}
		else if (*format >= '0' && *format <= '9')
		{
			parse->precision = ft_atoi(format);
			while (*format >= '0' && *format <= '9')
			{
				format++;
				i++;
			}
		}
	}
	return (i);
}
