/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_types.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/04 17:18:48 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/04 19:27:57 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void	init_types(t_parse *parse)
{
	parse->types.d = 0;
	parse->types.i = 0;
	parse->types.o = 0;
	parse->types.u = 0;
	parse->types.x = 0;
	parse->types.ux = 0;
	parse->types.e = 0;
	parse->types.ue = 0;
	parse->types.f = 0;
	parse->types.uf = 0;
	parse->types.g = 0;
	parse->types.ug = 0;
	parse->types.a = 0;
	parse->types.ua = 0;
	parse->types.c = 0;
	parse->types.s = 0;
	parse->types.p = 0;
	parse->types.n = 0;
	parse->types.percent = 0;
	parse->types.no_type = 0;
}

int		parse_gettype(const char *format, t_parse *parse)
{
	int i;

	i = 0;
	if ((*format == 'd' || *format == 'D') && ++i)
		parse->types.d = 1;
	else if ((*format == 'i') && ++i)
		parse->types.i = 1;
	else if ((*format == 'o' || *format == 'O') && ++i)
		parse->types.o = 1;
	else if ((*format == 'u' || *format == 'U') && ++i)
		parse->types.u = 1;
	else if ((*format == 'x') && ++i)
		parse->types.x = 1;
	else if ((*format == 'X') && ++i)
		parse->types.ux = 1;
	else if ((*format == 'e') && ++i)
		parse->types.e = 1;
	else if ((*format == 'E') && ++i)
		parse->types.ue = 1;
	else if ((*format == 'f') && ++i)
		parse->types.f = 1;
	else if ((*format == 'F') && ++i)
		parse->types.uf = 1;
	return (i);
}

int		parse_getmoretype(const char *format, t_parse *parse)
{
	int i;

	i = 0;
	if ((*format == 'g') && ++i)
		parse->types.g = 1;
	else if ((*format == 'G') && ++i)
		parse->types.ug = 1;
	else if ((*format == 'a') && ++i)
		parse->types.a = 1;
	else if ((*format == 'A') && ++i)
		parse->types.ua = 1;
	else if ((*format == 'c' || *format == 'C') && ++i)
		parse->types.c = 1;
	else if ((*format == 's' || *format == 'S') && ++i)
		parse->types.s = 1;
	else if ((*format == 'n') && ++i)
		parse->types.n = 1;
	else if ((*format == '%') && ++i)
		parse->types.percent = 1;
	return (i);
}

int		parse_type(const char *format, t_parse *parse)
{
	int i;

	i = 0;
	init_types(parse);
	if (*format == 'D' || *format == 'O' || *format == 'U'
			|| *format == 'C' || *format == 'S')
		parse->argsz.l = 1;
	i = parse_gettype(format, parse);
	if (!i)
		i = parse_getmoretype(format, parse);
	if (!i && *format == 'p' && ++i)
	{
		parse->types.p = 1;
		parse->flags.sharp = 1;
		parse->argsz.l = 1;
		parse->types.x = 1;
	}
	if (!i)
		parse->types.no_type++;
	else
		format++;
	return (i);
}
