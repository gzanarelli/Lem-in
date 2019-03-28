/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bfs.c                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/28 14:57:42 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/04 15:17:10 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"

static void	init_table(int *tab, int size, int val)
{
	int i;

	i = 0;
	while (i < size)
	{
		tab[i] = val;
		i++;
	}
}

static void	init_bfs(t_lem *l, int *tparent, t_queue **q)
{
	init_table(tparent, l->nbrooms, -1);
	tparent[l->start] = -2;
	*q = NULL;
	queue_push(q, l->start);
}

int			bfs(t_lem *l, int **tpath, int *tparent)
{
	int		i;
	int		cur;
	t_queue *q;

	cur = 0;
	init_bfs(l, tparent, &q);
	while ((cur = queue_pop(&q)) != -1)
	{
		i = -1;
		while (++i < l->nbrooms)
		{
			if (l->matrix[cur][i] && 1 - tpath[cur][i] > 0 && tparent[i] == -1)
			{
				tparent[i] = cur;
				if (i == l->end)
				{
					queue_delete(&q);
					return (1 - tpath[cur][i]);
				}
				queue_push(&q, i);
			}
		}
	}
	queue_delete(&q);
	return (0);
}

int			r_bfs(t_lem *l, int **tpath, int *tparent)
{
	int		i;
	int		cur;
	t_queue *q;

	cur = 0;
	init_bfs(l, tparent, &q);
	while ((cur = queue_pop(&q)) != -1)
	{
		i = l->nbrooms;
		while (--i >= 0)
		{
			if (l->matrix[cur][i] && 1 - tpath[cur][i] > 0 && tparent[i] == -1)
			{
				tparent[i] = cur;
				if (i == l->end)
				{
					queue_delete(&q);
					return (1 - tpath[cur][i]);
				}
				queue_push(&q, i);
			}
		}
	}
	queue_delete(&q);
	return (0);
}
