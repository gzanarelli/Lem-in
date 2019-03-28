/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_str.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/30 00:10:42 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/04 19:14:33 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "ft_printf.h"

int		fill_octet(char octet[4], wchar_t *wstmp, int flag)
{
	if (flag == 2)
	{
		octet[0] = 0xC0 | (char)((*wstmp >> 6) & 0x1F);
		octet[1] = 0x80 | (char)(*wstmp & 0x3F);
	}
	else if (flag == 3)
	{
		octet[0] = 0xE0 | (char)((*wstmp >> 12) & 0x0F);
		octet[1] = 0x80 | (char)((*wstmp >> 6) & 0x3F);
		octet[2] = 0x80 | (char)(*wstmp & 0x3F);
	}
	else if (flag == 4)
	{
		octet[0] = 0xF0 | (char)((*wstmp >> 18) & 0x07);
		octet[1] = 0x80 | (char)((*wstmp >> 12) & 0x3F);
		octet[2] = 0x80 | (char)((*wstmp >> 6) & 0x3F);
		octet[3] = 0x80 | (char)(*wstmp & 0x3F);
	}
	return (flag);
}

int		wchartochar(t_parse *parse, char **s, int size, wchar_t *wstmp)
{
	int		ret;
	char	octet[4];

	ret = -1;
	if (*wstmp <= 0x7FF)
	{
		if (!(parse->precision > -1 && size + 2 > parse->precision))
			ret = fill_octet(octet, wstmp, 2);
	}
	else if (*wstmp <= 0xFFFF)
	{
		if (!(parse->precision > -1 && size + 3 > parse->precision))
			ret = fill_octet(octet, wstmp, 3);
	}
	else if (*wstmp <= 0x10FFFF)
	{
		if (!(parse->precision > -1 && size + 4 > parse->precision))
			ret = fill_octet(octet, wstmp, 4);
	}
	if (ret != -1)
	{
		*s = ft_realloc(*s, size, size + ret);
		ft_memcpy(&(*s)[size], octet, ret);
	}
	return (ret);
}

int		wstrtostr(t_parse *parse, char **s, int size, wchar_t *wstmp)
{
	int res;

	while (*wstmp != L'\0')
	{
		if (MB_CUR_MAX == 1 || *wstmp <= 0x7F)
		{
			if (parse->precision > -1 && size + 1 > parse->precision)
				break ;
			*s = ft_realloc(*s, size, size + 1);
			ft_memcpy(&(*s)[size], wstmp, 1);
			size++;
		}
		else
		{
			res = wchartochar(parse, s, size, wstmp);
			if (res != -1)
				size += res;
			else
				break ;
		}
		wstmp++;
	}
	return (size);
}

int		get_wstr(t_parse *parse, va_list *arg_lst)
{
	char	*s;
	int		size;
	wchar_t	*wstmp;

	size = 0;
	wstmp = va_arg(*arg_lst, wchar_t *);
	s = NULL;
	if (wstmp == NULL && !parse->flags.zero)
	{
		s = ft_strdup("(null)");
		size = 6;
	}
	if (wstmp != NULL)
		size = wstrtostr(parse, &s, 0, wstmp);
	if (s == NULL)
		s = ft_memalloc(sizeof(char));
	size = get_width(parse, &s, size);
	if (s != NULL)
	{
		if (parse->width > size)
			size += parse->width;
	}
	write(1, s, size);
	free(s);
	return (size - 1);
}

int		get_str(t_parse *parse, va_list *arg_lst)
{
	int		size;
	char	*s;
	char	*stmp;

	if (parse->argsz.l)
		return (get_wstr(parse, arg_lst));
	stmp = va_arg(*arg_lst, char *);
	s = NULL;
	if (stmp == NULL && !parse->flags.zero)
		s = ft_strdup("(null)");
	else if (stmp == NULL && parse->flags.zero)
		s = ft_memalloc(sizeof(char));
	else if (parse->precision != -1 && parse->precision < (int)ft_strlen(stmp))
		s = ft_strsub(stmp, 0, parse->precision);
	else
		s = ft_strdup(stmp);
	size = get_width(parse, &s, ft_strlen(s));
	write(1, s, size);
	free(s);
	return (size - 1);
}
