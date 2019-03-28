/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_realloc.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/09 19:25:37 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/20 00:23:15 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	void *tmp;

	tmp = malloc(new_size);
	if (tmp != NULL && ptr != NULL && old_size > 0)
	{
		if (new_size > old_size)
			ft_memcpy(tmp, ptr, old_size);
		else
			ft_memcpy(tmp, ptr, new_size);
	}
	if (ptr != NULL)
		free(ptr);
	return (tmp);
}
