/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_prec.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/31 18:01:51 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/04 17:14:27 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		no_precision(t_parse *parse, char **s, int len)
{
	if (parse->precision <= len)
	{
		if ((*s)[0] != '-' && (parse->flags.space || parse->flags.plus))
		{
			*s = ft_realloc(*s, len, len + 2);
			ft_memmove(*s + 1, *s, len + 1);
			if (parse->flags.plus)
				(*s)[0] = '+';
			else if (parse->flags.space)
				(*s)[0] = ' ';
		}
		return (1);
	}
	return (0);
}

int		precise_precision(t_parse *parse, char **s)
{
	int neg;

	neg = 0;
	if ((*s)[0] == '-')
	{
		neg = 1;
		parse->precision++;
	}
	else if (parse->flags.space || parse->flags.plus)
		parse->precision++;
	else if ((*s)[1] == 'x' || (*s)[1] == 'X')
	{
		neg = 2;
		parse->precision += 4;
	}
	return (neg);
}

void	add_sign(t_parse *parse, char *res, int neg)
{
	if (neg == 1)
		res[0] = '-';
	else if (parse->flags.plus)
		res[0] = '+';
	else if (parse->flags.space)
		res[0] = ' ';
	else if (neg == 2)
	{
		res[0] = '0';
		res[1] = 'x';
	}
}

int		get_prec_i(t_parse *parse, char **s, int len)
{
	int		i;
	int		j;
	int		neg;
	char	*res;

	if ((*s)[0] == '-')
		parse->precision++;
	if (no_precision(parse, s, len))
		return (len + (parse->flags.space || parse->flags.plus));
	neg = precise_precision(parse, s);
	res = malloc(sizeof(char) * (parse->precision + 1));
	i = 0;
	parse->precision -= len;
	while (i < parse->precision)
		res[i++] = '0';
	j = neg;
	while ((*s)[j])
		res[i++] = (*s)[j++];
	res[i] = '\0';
	add_sign(parse, res, neg);
	free(*s);
	*s = res;
	return (i);
}
