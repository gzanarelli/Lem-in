/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_char.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/30 00:00:25 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/04 19:15:12 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		get_char(t_parse *parse, va_list *arg_lst)
{
	char	*s;
	int		d;
	int		ret;

	if (parse->argsz.l)
		return (get_wchar(parse, arg_lst));
	d = va_arg(*arg_lst, int);
	s = ft_realloc(NULL, 0, 2);
	s[0] = (char)d;
	s[1] = '\0';
	ret = get_width(parse, &s, 1);
	write(1, s, ret);
	free(s);
	return (ret - 1);
}

int		fill_wintoctet(char octet[4], wint_t d, int flag)
{
	if (flag == 2)
	{
		octet[0] = 0xC0 | (char)((d >> 6) & 0x1F);
		octet[1] = 0x80 | (char)(d & 0x3F);
	}
	else if (flag == 3)
	{
		octet[0] = 0xE0 | (char)((d >> 12) & 0x0F);
		octet[1] = 0x80 | (char)((d >> 6) & 0x3F);
		octet[2] = 0x80 | (char)(d & 0x3F);
	}
	else if (flag == 4)
	{
		octet[0] = 0xF0 | (char)((d >> 18) & 0x07);
		octet[1] = 0x80 | (char)((d >> 12) & 0x3F);
		octet[2] = 0x80 | (char)((d >> 6) & 0x3F);
		octet[3] = 0x80 | (char)(d & 0x3F);
	}
	return (flag);
}

int		winttochar(char **s, wint_t d)
{
	int		ret;
	char	octet[4];

	ret = -1;
	if (d <= 0x7FF)
		ret = fill_wintoctet(octet, d, 2);
	else if (d <= 0xFFFF)
		ret = fill_wintoctet(octet, d, 3);
	else if (d <= 0x10FFFF)
		ret = fill_wintoctet(octet, d, 4);
	if (ret != -1)
	{
		*s = ft_realloc(*s, 0, ret);
		ft_memcpy(*s, octet, ret);
	}
	return (ret);
}

int		get_wchar(t_parse *parse, va_list *arg_lst)
{
	wint_t	d;
	char	*s;
	int		size;
	int		res;

	size = 0;
	s = NULL;
	d = va_arg(*arg_lst, wint_t);
	if (MB_CUR_MAX == 1 || d <= 0x7F)
	{
		s = ft_realloc(s, 0, 1);
		ft_memcpy(s, &d, 1);
		size = 1;
	}
	else
	{
		res = winttochar(&s, d);
		if (res != -1)
			size = res;
	}
	if (parse->width > 1)
		size = get_width(parse, &s, size);
	write(1, s, size);
	free(s);
	return (size - 1);
}
