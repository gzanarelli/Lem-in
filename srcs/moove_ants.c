/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   moove_ants.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/02 15:18:47 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/04 17:27:03 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"

void		moove_ants(t_lem *l)
{
	int i;
	int a;

	i = -1;
	while (++i < l->nb_path)
	{
		a = l->tab_path[i].size - 1;
		while (--a >= 0)
		{
			if (l->tab_path[i].path[a][1] != 0)
			{
				l->tab_path[i].path[a + 1][1] = l->tab_path[i].path[a][1];
				l->tab_path[i].path[a][1] = 0;
				if (l->tab_path[i].path[a + 1][0] == l->end)
					l->ants--;
				ft_printf("L%d-%s ", l->tab_path[i].path[a + 1][1],
				l->map[l->tab_path[i].path[a + 1][0]]);
			}
		}
	}
}

static void	verif_path_two(t_lem *l, int j, int f)
{
	if (l->tab_path[j].size < l->tab_path[j + 1].size)
	{
		if (l->tab_path[0].size + f <= l->tab_path[1].size
				&& l->stop + 1 != l->nb_path)
		{
			l->tab_path[1].ope = 1;
			l->stop++;
		}
	}
	else if (l->tab_path[j].size > l->tab_path[j + 1].size)
	{
		if (l->tab_path[1].size + f <= l->tab_path[0].size
				&& l->stop + 1 != l->nb_path)
		{
			l->tab_path[0].ope = 1;
			l->stop++;
		}
	}
}

static void	verif_path_ants(t_lem *l)
{
	int k;
	int res[2];

	k = -1;
	res[1] = 0;
	res[0] = 0;
	while (++k < l->nb_path)
	{
		if (l->tab_path[k].size > res[0])
		{
			res[0] = l->tab_path[k].size;
			res[1] = k;
		}
	}
	l->tab_path[res[1]].ope = 1;
	l->stop++;
}

int			verif_path(t_lem *l, int ants_tt, int ants, int i)
{
	int f;
	int j;

	j = 0;
	f = ants_tt - ants;
	if (l->nb_path > 1)
		verif_path_two(l, j, f);
	if (f < l->nb_path && l->stop + 1 != l->nb_path)
		verif_path_ants(l);
	while (j < l->nb_path && (l->stop + 1) <= l->nb_path)
	{
		if (f + l->nb_path < l->tab_path[j].size &&
		((l->stop + 1) != l->nb_path))
		{
			l->tab_path[j].ope = 1;
			l->stop++;
		}
		j++;
	}
	if (l->tab_path[i].ope == 0)
		return (0);
	return (1);
}

void		enter_ants(t_lem *l)
{
	int i;
	int ants;
	int ants_tt;

	ants = 0;
	ants_tt = l->ants;
	if (l->nb_path == 2 && l->ants < l->nb_path)
		verif_path(l, ants_tt, ants, 0);
	while (l->ants && (i = -1))
	{
		ants != 0 ? moove_ants(l) : 0;
		while (++i < l->nb_path && ants < ants_tt)
		{
			if (l->tab_path[i].ope == 1)
				continue ;
			else if (l->tab_path[i].path[0][1] == 0 &&
			verif_path(l, ants_tt, ants, i) == 0)
			{
				l->tab_path[i].path[0][1] = ++ants;
				ft_printf("L%d-%s ", l->tab_path[i].path[0][1],
				l->map[l->tab_path[i].path[0][0]]);
			}
		}
		ft_printf("\n");
	}
}
