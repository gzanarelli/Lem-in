/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strlcat.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/02 17:29:46 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/03 19:39:03 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	size_s1;
	size_t	i;

	size_s1 = ft_strlen(dst);
	if (size_s1 >= size)
		return (size + ft_strlen(src));
	i = 0;
	while (i + size_s1 < size - 1 && src[i] != '\0')
	{
		dst[size_s1 + i] = src[i];
		i++;
	}
	dst[size_s1 + i] = '\0';
	return (size_s1 + ft_strlen(src));
}
