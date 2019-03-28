/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strmap.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/03 23:07:25 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 19:33:30 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*sres;
	int		i;

	sres = NULL;
	if (s)
		sres = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (sres == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		sres[i] = f(s[i]);
		i++;
	}
	sres[i] = '\0';
	return (sres);
}
