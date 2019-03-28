/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_freetab.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/04 15:39:41 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/04 15:40:12 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	**ft_freetab(void **t, size_t len)
{
	if (t == NULL)
		return (t);
	while (len)
	{
		if (t[len] != NULL)
			free(t[len]);
		len--;
	}
	free(t);
	return (t);
}
