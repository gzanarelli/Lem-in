/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   save_paths.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/02 15:17:45 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/07 13:18:03 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"

static int	queue_path(t_lem *l, int **tpath, int lasti, t_queue **q)
{
	int cnt;
	int j;

	tpath[l->start][lasti] = 0;
	cnt = 0;
	j = -1;
	while (++j < l->nbrooms)
	{
		if (tpath[lasti][j] == 1)
		{
			tpath[lasti][j] = 0;
			cnt++;
			queue_push(q, lasti);
			lasti = j;
			j = -1;
		}
	}
	if (lasti != l->end)
		queue_delete(q);
	return (cnt);
}

static void	fill_path(t_lem *l, int cnt, t_queue **q, int a)
{
	int k;

	if (!(l->tab_path[a].path = malloc(sizeof(int *) * (cnt + 1))))
		exit_err("Error on malloc, could not allocate paths\n");
	l->tab_path[a].size = cnt + 1;
	l->tab_path[a].ope = 0;
	k = 0;
	while (*q)
	{
		if (!(l->tab_path[a].path[k] = malloc(sizeof(int) * 2)))
			exit_err("Error on malloc, could not allocate paths\n");
		l->tab_path[a].path[k][0] = queue_pop(q);
		l->tab_path[a].path[k][1] = 0;
		k++;
	}
	if (!(l->tab_path[a].path[k] = malloc(sizeof(int) * 2)))
		exit_err("Error on malloc, could not allocate paths\n");
	l->tab_path[a].path[k][0] = l->end;
	l->tab_path[a].path[k][1] = 0;
}

void		print_paths(t_lem *l, int **tpath, t_edkarp *ek)
{
	t_queue	*q;
	int		cnt;
	int		a;
	int		i;

	q = NULL;
	a = 0;
	if (!(l->tab_path = malloc(sizeof(t_path) * ek->maxflow)))
		exit_err("Error on malloc, could not allocate paths\n");
	l->nb_path = ek->maxflow;
	i = -1;
	while (++i < l->nbrooms)
	{
		if (tpath[l->start][i] == 1)
		{
			cnt = queue_path(l, tpath, i, &q);
			if (q)
			{
				fill_path(l, cnt, &q, a);
				a++;
			}
			queue_delete(&q);
		}
	}
}
