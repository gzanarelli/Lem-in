/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_imaxtoa_base.c                                .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/27 16:04:57 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/27 17:06:59 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

#define SIZE 20

static char	*fill_str(int *i, char *sres, intmax_t n, const char *base)
{
	int size;
	int base_len;

	size = SIZE;
	base_len = ft_strlen(base);
	while (n > 0)
	{
		if (*i >= size)
		{
			if (!(sres = ft_realloc(sres, size, size * 2 + 2)) && !(size *= 2))
				return (NULL);
		}
		sres[*i] = base[n % base_len];
		n /= base_len;
		(*i)++;
	}
	return (sres);
}

static char	*handle_long_min(char *sres, intmax_t n, const char *base)
{
	sres = ft_imaxtoa_base(n + 1, base);
	sres[ft_strlen(sres) - 1]++;
	return (sres);
}

char		*ft_imaxtoa_base(intmax_t n, const char *base)
{
	char	*sres;
	int		i;
	int		sign;

	sres = NULL;
	if (n == LONG_MIN)
		return (handle_long_min(sres, n, base));
	if (!(sres = malloc(sizeof(char) * (SIZE + 2))))
		return (NULL);
	sign = n < 0 ? 1 : 0;
	n = n < 0 ? -n : n;
	i = 0;
	(!n) ? sres[i++] = base[0] : 0;
	fill_str(&i, sres, n, base);
	(sign) ? sres[i++] = '-' : 0;
	sres[i] = '\0';
	if (!(sres = ft_realloc(sres, ft_strlen(sres) + 1, ft_strlen(sres) + 1)))
		return (NULL);
	return (ft_strrev(sres));
}
