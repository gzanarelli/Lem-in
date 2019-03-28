/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tmp.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/24 17:07:31 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/04 19:35:07 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <wchar.h>
# include <unistd.h>
# include <stdarg.h>
# include <stdlib.h>

typedef struct	s_flags
{
	int			minus;
	int			plus;
	int			zero;
	int			space;
	int			sharp;
}				t_flags;

typedef struct	s_argsz
{
	int			hh;
	int			h;
	int			l;
	int			ll;
	int			j;
	int			t;
	int			z;
	int			ul;
}				t_argsz;

typedef struct	s_types
{
	int			d;
	int			i;
	int			o;
	int			u;
	int			x;
	int			ux;
	int			e;
	int			ue;
	int			f;
	int			uf;
	int			g;
	int			ug;
	int			a;
	int			ua;
	int			c;
	int			s;
	int			p;
	int			n;
	int			percent;
	int			no_type;
}				t_types;

typedef struct	s_parse
{
	t_flags		flags;
	int			width;
	int			precision;
	t_argsz		argsz;
	t_types		types;
}				t_parse;

int				ft_printf(const char *format, ...);
int				print_percent(t_parse *parse);
int				print_double(t_parse *parse, va_list *arg_lst);
int				print_n(t_parse *parse);
int				parsing(const char *format, t_parse *parse);
void			parse_ignore(t_parse *parse);
int				parse_flags(const char *format, t_flags *flags);
int				parse_width(const char *format, t_parse *parse);
int				parse_precision(const char *format, t_parse *parse);
int				parse_size(const char *format, t_argsz *argsz);
int				parse_type(const char *format, t_parse *parse);
char			*ft_imaxtoa_base(intmax_t n, const char *base);
char			*ft_uimaxtoa_base(uintmax_t n, const char *base);

int				get_int(t_parse *parse, va_list *arg_lst);
int				get_uint(t_parse *parse, va_list *arg_lst);
int				get_char(t_parse *parse, va_list *arg_lst);
int				get_wchar(t_parse *parse, va_list *arg_lst);
int				fill_octet(char octet[4], wchar_t *wstmp, int flag);
int				wchartochar(t_parse *parse, char **s, int size, wchar_t *wstmp);
int				wstrtostr(t_parse *parse, char **s, int size, wchar_t *wstmp);
int				get_wstr(t_parse *parse, va_list *arg_lst);
int				get_str(t_parse *parse, va_list *arg_lst);
int				get_width(t_parse *parse, char **s, int len);
int				get_prec_i(t_parse *parse, char **s, int len);

#endif
