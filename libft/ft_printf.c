/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/25 18:21:52 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/04 19:25:14 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int	fill_arg(t_parse *parse, va_list *arg_lst)
{
	int j;

	j = 0;
	if (parse->types.d || parse->types.i)
		j = get_int(parse, arg_lst);
	else if (parse->types.o || parse->types.u || parse->types.x
			|| parse->types.ux || parse->types.p)
		j = get_uint(parse, arg_lst);
	else if (parse->types.s)
		j = get_str(parse, arg_lst);
	else if (parse->types.c)
		j = get_char(parse, arg_lst);
	else if (parse->types.e || parse->types.ue || parse->types.f
			|| parse->types.uf || parse->types.g || parse->types.ug
			|| parse->types.a || parse->types.ua)
		j = print_double(parse, arg_lst);
	else if (parse->types.n)
		j = print_n(parse);
	else if (parse->types.percent)
		j = print_percent(parse);
	return (j);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg_lst;
	t_parse	parse;
	int		i;

	va_start(arg_lst, format);
	i = 0;
	while (*format != '\0')
	{
		if (*format == '%')
		{
			format++;
			format += parsing(format, &parse) - 1;
			if (!parse.types.no_type)
				i += fill_arg(&parse, &arg_lst);
			else
				i--;
		}
		else
			write(1, format, 1);
		format++;
		i++;
	}
	va_end(arg_lst);
	return (i);
}
