/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strsplit.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 23:41:52 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 19:51:51 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsplit(char const *s, char c)
{
	char	**sres;
	int		i;
	int		k;

	if (s)
		sres = malloc(sizeof(char *) * (ft_strcount_words((char *)s, c) + 1));
	if (!s || sres == NULL)
		return (NULL);
	k = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i] != '\0')
		{
			sres[k] = ft_strsub((char *)s, i, ft_strlen_c((char *)&s[i], c));
			if (sres[k] == NULL)
				return ((char **)ft_freetab((void **)sres, k));
			i += ft_strlen_c((char *)&s[i], c);
			k++;
		}
	}
	sres[k] = 0;
	return (sres);
}
