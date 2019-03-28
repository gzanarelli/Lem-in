/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/25 16:03:49 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/04 19:25:43 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		parsing(const char *format, t_parse *parse)
{
	int i;

	i = 0;
	i += parse_flags(format, &parse->flags);
	i += parse_width(format + i, parse);
	i += parse_precision(format + i, parse);
	i += parse_size(format + i, &parse->argsz);
	i += parse_type(format + i, parse);
	format += i;
	parse_ignore(parse);
	return (i);
}

void	parse_ignore(t_parse *parse)
{
	if (parse->flags.zero && parse->flags.minus)
		parse->flags.zero = 0;
	if (parse->flags.zero && parse->precision > 0
			&& (parse->types.d || parse->types.i || parse->types.o
				|| parse->types.u || parse->types.x || parse->types.ux))
		parse->flags.zero = 0;
	if (parse->flags.space && parse->flags.plus)
		parse->flags.space = 0;
	if (!(parse->types.a || parse->types.ua || parse->types.d
			|| parse->types.e || parse->types.ue || parse->types.f
			|| parse->types.uf || parse->types.g || parse->types.ug
			|| parse->types.i))
	{
		parse->flags.space = 0;
		parse->flags.plus = 0;
	}
	if (parse->flags.sharp && (parse->types.d || parse->types.i
				|| parse->types.u || parse->types.c || parse->types.s))
		parse->flags.sharp = 0;
}
