/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_int.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/30 00:07:55 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/04 19:29:05 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

intmax_t	get_intparam(t_parse *parse, va_list *arg_lst)
{
	intmax_t	d;

	if (parse->argsz.l)
		d = va_arg(*arg_lst, long);
	else if (parse->argsz.hh)
		d = (char)va_arg(*arg_lst, int);
	else if (parse->argsz.h)
		d = (short int)va_arg(*arg_lst, int);
	else if (parse->argsz.ll)
		d = va_arg(*arg_lst, long long);
	else if (parse->argsz.j)
		d = va_arg(*arg_lst, intmax_t);
	else if (parse->argsz.t)
		d = va_arg(*arg_lst, ptrdiff_t);
	else if (parse->argsz.z)
		d = va_arg(*arg_lst, size_t);
	else
		d = va_arg(*arg_lst, int);
	return (d);
}

int			get_int(t_parse *parse, va_list *arg_lst)
{
	intmax_t	d;
	char		*s;

	d = get_intparam(parse, arg_lst);
	s = ft_imaxtoa_base(d, "0123456789");
	if (d == 0 && parse->precision == 0)
	{
		parse->precision = -1;
		s[0] = '\0';
	}
	d = get_prec_i(parse, &s, ft_strlen(s));
	d = get_width(parse, &s, ft_strlen(s));
	write(1, s, d);
	free(s);
	return (d - 1);
}

uintmax_t	get_uintparam(t_parse *parse, va_list *arg_lst)
{
	uintmax_t	d;

	if (parse->argsz.l)
		d = va_arg(*arg_lst, unsigned long);
	else if (parse->argsz.ll)
		d = va_arg(*arg_lst, unsigned long long);
	else if (parse->argsz.hh)
		d = (unsigned char)va_arg(*arg_lst, unsigned int);
	else if (parse->argsz.h)
		d = (unsigned short int)va_arg(*arg_lst, unsigned int);
	else if (parse->argsz.l)
		d = va_arg(*arg_lst, unsigned long);
	else if (parse->argsz.ll)
		d = va_arg(*arg_lst, unsigned long long);
	else if (parse->argsz.j)
		d = va_arg(*arg_lst, uintmax_t);
	else if (parse->argsz.t)
		d = va_arg(*arg_lst, ptrdiff_t);
	else if (parse->argsz.z)
		d = va_arg(*arg_lst, size_t);
	else
		d = va_arg(*arg_lst, unsigned int);
	return (d);
}

char		*random_peculiar_cases(t_parse *parse, char *s, uintmax_t d)
{
	if (!d && !parse->precision && !(parse->types.o && parse->flags.sharp))
	{
		parse->precision = -1;
		s[0] = '\0';
	}
	if (parse->types.p && d == 0)
	{
		s = ft_realloc(s, ft_strlen(s), ft_strlen(s) + 3);
		ft_memmove(s + 2, s, ft_strlen(s) + 2);
		s[0] = '0';
		s[1] = 'x';
	}
	if (parse->flags.sharp && d != 0 && !parse->types.o)
	{
		s = ft_realloc(s, ft_strlen(s), ft_strlen(s) + 3);
		ft_memmove(s + 2, s, ft_strlen(s) + 2);
		s[0] = '0';
		if (parse->types.x)
			s[1] = 'x';
		else if (parse->types.ux)
			s[1] = 'X';
	}
	return (s);
}

int			get_uint(t_parse *parse, va_list *arg_lst)
{
	uintmax_t	d;
	char		*s;

	d = get_uintparam(parse, arg_lst);
	if (parse->types.o)
		s = ft_uimaxtoa_base(d, "01234567");
	else if (parse->types.x)
		s = ft_uimaxtoa_base(d, "0123456789abcdef");
	else if (parse->types.ux)
		s = ft_uimaxtoa_base(d, "0123456789ABCDEF");
	else
		s = ft_uimaxtoa_base(d, "0123456789");
	s = random_peculiar_cases(parse, s, d);
	if (parse->flags.sharp && parse->types.o && d != 0)
	{
		s = ft_realloc(s, ft_strlen(s), ft_strlen(s) + 2);
		ft_memmove(s + 1, s, ft_strlen(s) + 1);
		s[0] = '0';
	}
	d = get_prec_i(parse, &s, ft_strlen(s));
	d = get_width(parse, &s, ft_strlen(s));
	write(1, s, d);
	free(s);
	return (d - 1);
}
