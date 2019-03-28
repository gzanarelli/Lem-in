/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_uimaxtoa_base.c                               .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/27 16:45:53 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/27 17:06:01 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

#define SIZE 20

char	*ft_uimaxtoa_base(uintmax_t n, const char *base)
{
	char	*sres;
	int		i;
	int		base_len;
	int		size;

	base_len = ft_strlen(base);
	size = SIZE;
	if (!(sres = malloc(sizeof(char) * (size + 2))))
		return (NULL);
	i = 0;
	(!n) ? sres[i++] = base[0] : 0;
	while (n > 0)
	{
		if (i >= size && (size = size * 2))
			if (!(sres = ft_realloc(sres, size, size * 2 + 2)))
				return (NULL);
		sres[i++] = base[n % base_len];
		n /= base_len;
	}
	sres[i] = '\0';
	if (!(sres = ft_realloc(sres, i + 1, i + 1)))
		return (NULL);
	return (ft_strrev(sres));
}
