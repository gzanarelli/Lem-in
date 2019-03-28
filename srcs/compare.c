/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   compare.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/03 18:43:07 by gzanarel     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/04 16:06:36 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"

static int	count(t_lem *l, t_edkarp *e)
{
	int i;
	int j;
	int cnt;

	cnt = 0;
	i = -1;
	while (++i < l->nbrooms)
	{
		j = -1;
		while (++j < l->nbrooms)
		{
			if (e->tpath[i][j] == 1)
				cnt++;
		}
	}
	return (cnt);
}

static void	no_pasaran(t_lem *l, t_edkarp *ek, t_edkarp *r_ek)
{
	write(1, "ERROR\n", 6);
	free_lem(l);
	free_edkarp(l, ek);
	free_edkarp(l, r_ek);
	exit(0);
}

t_edkarp	*compare_flow(t_lem *l, t_edkarp *ek, t_edkarp *r_ek)
{
	int cnt;
	int cnt_r;

	if (!ek->maxflow && !r_ek->maxflow)
		no_pasaran(l, ek, r_ek);
	cnt = count(l, ek);
	cnt_r = count(l, r_ek);
	if (cnt < cnt_r)
		return (ek);
	return (r_ek);
}
