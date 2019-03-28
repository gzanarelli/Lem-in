/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   queue.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/28 15:00:01 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/04 14:44:31 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"

void	queue_view(t_queue **q)
{
	t_queue *cur;

	cur = *q;
	while (cur)
	{
		cur = cur->next;
	}
}

void	queue_push(t_queue **q, int val)
{
	t_queue *crawler;
	t_queue *new;

	new = malloc(sizeof(t_queue));
	if (new == NULL)
	{
		write(2, "A problem occurred adding a element in queue...\n", 48);
		exit(1);
	}
	new->next = NULL;
	new->val = val;
	if (*q == NULL)
		*q = new;
	else
	{
		crawler = *q;
		while (crawler->next != NULL)
			crawler = crawler->next;
		crawler->next = new;
	}
}

void	queue_delete(t_queue **q)
{
	t_queue *current;
	t_queue *next;

	current = *q;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*q = NULL;
}

int		queue_pop(t_queue **q)
{
	t_queue	*next;
	int		res;

	if (*q == NULL)
		return (-1);
	res = (*q)->val;
	next = (*q)->next;
	free(*q);
	*q = next;
	return (res);
}
