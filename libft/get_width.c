/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_width.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/31 16:47:36 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/04 16:57:10 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

void	width_zero(char **s, char *res)
{
	if ((*s)[0] == '+' || (*s)[0] == '-' || (*s)[0] == ' ')
	{
		res[0] = (*s)[0];
		(*s)[0] = '0';
	}
	else if ((*s)[1] == 'x' || (*s)[1] == 'X')
	{
		res[1] = (*s)[1];
		(*s)[1] = '0';
	}
}

int		fill_width(t_parse *parse, char *res, int i)
{
	while (i < parse->width)
	{
		if (parse->flags.zero)
			res[i] = '0';
		else
			res[i] = ' ';
		i++;
	}
	return (i);
}

int		get_width(t_parse *parse, char **s, int len)
{
	int		i;
	char	*res;

	if (parse->width <= len)
		return (len);
	res = malloc(sizeof(char) * (parse->width + 1));
	i = 0;
	if (parse->flags.minus)
	{
		ft_memcpy(res, *s, len);
		i = len;
	}
	else
		parse->width -= len;
	i = fill_width(parse, res, i);
	if (!parse->flags.minus)
	{
		parse->flags.zero ? width_zero(s, res) : 0;
		ft_memcpy(&res[i], *s, len);
		i += len;
	}
	res[i] = '\0';
	free(*s);
	*s = res;
	return (i);
}
