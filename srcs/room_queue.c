/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   room_queue.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/31 12:31:45 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/04 14:44:16 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"

void	roomq_push(t_roomq **rq, int special, char *name)
{
	t_roomq *crawler;
	t_roomq *new;

	new = malloc(sizeof(t_roomq));
	if (new == NULL)
	{
		write(2, "A problem occurred adding a element in roomq...\n", 48);
		exit(1);
	}
	new->next = NULL;
	new->name = name;
	new->special = special;
	if (*rq == NULL)
		*rq = new;
	else
	{
		crawler = *rq;
		while (crawler->next != NULL)
			crawler = crawler->next;
		crawler->next = new;
	}
}

void	roomq_delete(t_roomq **rq)
{
	t_roomq *current;
	t_roomq *next;

	current = *rq;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
	*rq = NULL;
}

void	roomq_del_first(t_roomq **rq)
{
	t_roomq *next;

	if (*rq != NULL)
	{
		next = (*rq)->next;
		free(*rq);
		*rq = next;
	}
}
