/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_lstmap.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/05 15:00:05 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/05 19:16:21 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *crawler;
	t_list *new;
	t_list *tmp;
	t_list *last;
	t_list *first;

	first = NULL;
	new = NULL;
	crawler = lst;
	while (crawler != NULL)
	{
		tmp = f(crawler);
		last = new;
		new = ft_lstnew(tmp->content, tmp->content_size);
		if (new == NULL)
			return (NULL);
		if (last == NULL)
			first = new;
		else
			last->next = new;
		crawler = crawler->next;
	}
	return (first);
}
