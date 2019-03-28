/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_undef.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/04 18:52:08 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/04 19:17:04 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_percent(t_parse *parse)
{
	int		j;
	char	*s;

	s = malloc(2);
	s[0] = '%';
	s[1] = '\0';
	j = get_width(parse, &s, 1);
	write(1, s, j);
	free(s);
	return (j - 1);
}

int	print_double(t_parse *parse, va_list *arg_lst)
{
	double db;

	parse->precision = parse->width * 0;
	db = va_arg(*arg_lst, double);
	write(1, "[double not implemented]",
			ft_strlen("[double not implemented]") - 1);
	return (ft_strlen("[double not implemented]") - 1);
}

int	print_n(t_parse *parse)
{
	unsigned int n;

	n = 0;
	parse->precision = parse->width * 0;
	write(1, "[n not implemented]", ft_strlen("[n not implemented]") - 1);
	return (ft_strlen("[n not implemented]") - 1);
}
