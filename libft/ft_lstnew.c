/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstnew.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/05 14:30:32 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 16:42:24 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *new;

	new = malloc(sizeof(*new));
	if (new == NULL)
		return (NULL);
	new->content = NULL;
	new->content_size = 0;
	if (content != NULL)
	{
		new->content = malloc(sizeof(*content) * content_size);
		if (new->content == NULL)
		{
			ft_memdel((void **)&new);
			return (NULL);
		}
		new->content = ft_memcpy((void *)new->content, content, content_size);
		new->content_size = content_size;
	}
	new->next = NULL;
	return (new);
}
