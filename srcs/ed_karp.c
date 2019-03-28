/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ed_karp.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/28 13:07:51 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/07 13:23:33 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"

static void	init_tables(t_lem *l, int *tparent, int **tpath)
{
	int i;
	int j;

	i = -1;
	while (++i < l->nbrooms)
	{
		j = -1;
		while (++j < l->nbrooms)
		{
			tpath[i][j] = 0;
		}
	}
	i = -1;
	while (++i < l->nbrooms)
		tparent[i] = 0;
}

static void	init(t_lem *l, t_edkarp *ek)
{
	int i;

	ek->tparent = malloc(sizeof(int) * l->nbrooms);
	ek->tpath = malloc(sizeof(int *) * l->nbrooms);
	if (!ek->tparent || !ek->tpath)
		exit_err("Error on malloc, could not allocate edkarp\n");
	i = 0;
	while (i < l->nbrooms)
	{
		ek->tpath[i] = malloc(sizeof(int) * l->nbrooms);
		if (ek->tpath[i] == NULL)
			exit_err("Error on malloc, could not allocate edkarp\n");
		i++;
	}
	ek->maxflow = 0;
	init_tables(l, ek->tparent, ek->tpath);
}

static void	fill_tflux(t_lem *l, t_edkarp *ek)
{
	int current;
	int next;

	current = l->end;
	while (current != l->start)
	{
		next = ek->tparent[current];
		ek->tpath[next][current] += ek->flow;
		ek->tpath[current][next] -= ek->flow;
		current = next;
	}
}

static void	remove_duplicates(t_lem *l, t_edkarp *ek)
{
	int i;
	int j;

	i = -1;
	while (++i < l->nbrooms)
	{
		if (i == l->end || i == l->start)
			continue ;
		j = -1;
		while (++j < l->nbrooms)
		{
			if (ek->tpath[i][j] == 1)
			{
				while (++j < l->nbrooms)
				{
					if (ek->tpath[i][j] == 1)
					{
						ek->tpath[i][j] = 0;
						ek->tpath[j][i] = 0;
						ek->maxflow--;
					}
				}
			}
		}
	}
}

t_edkarp	*edmondkarp(t_lem *l)
{
	t_edkarp *ek;

	ek = malloc(sizeof(t_edkarp));
	if (ek == NULL)
		exit_err("Error on malloc, could not allocate edkarp\n");
	init(l, ek);
	while (1)
	{
		ek->flow = bfs(l, ek->tpath, ek->tparent);
		if (ek->flow == 0)
			break ;
		ek->maxflow += ek->flow;
		fill_tflux(l, ek);
		if (ek->maxflow >= l->ants)
			break ;
	}
	remove_duplicates(l, ek);
	return (ek);
}
