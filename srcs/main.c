/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/20 14:30:24 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/04 16:07:22 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"

void		init_lem(t_lem *l)
{
	l->ants = 0;
	l->start = -1;
	l->end = -1;
	l->nbrooms = 0;
	l->s_link = 0;
	l->e_link = 0;
	l->map = NULL;
	l->matrix = NULL;
	l->max_flow = 0;
	l->stop = 0;
	l->nb_path = 0;
	l->tab_path = NULL;
}

static int	check_valid_map(t_lem *l)
{
	if (l->ants <= 0)
		return (0);
	if (l->nbrooms < 2)
		return (0);
	if (l->start == -1)
		return (0);
	if (l->end == -1)
		return (0);
	if (l->s_link <= 0)
		return (0);
	if (l->e_link <= 0)
		return (0);
	return (1);
}

void		solve_it(int ants, char *name)
{
	int i;

	i = 0;
	while (i < ants)
	{
		ft_putchar('L');
		ft_putnbr(i + 1);
		ft_putchar('-');
		ft_putstr(name);
		if (i + 1 < ants)
			ft_putchar(' ');
		i++;
	}
	ft_putchar('\n');
}

static int	error_map(t_lem *l)
{
	write(1, "ERROR\n", 6);
	free_lem(l);
	return (0);
}

int			main(void)
{
	t_lem		l;
	t_edkarp	*ek;
	t_edkarp	*r_ek;
	t_edkarp	*res;

	init_lem(&l);
	parse_map(&l);
	if (!check_valid_map(&l))
		return (error_map(&l));
	if (l.matrix[l.start][l.end])
	{
		solve_it(l.ants, l.map[l.end]);
		free_lem(&l);
		return (0);
	}
	ek = edmondkarp(&l);
	r_ek = r_edmondkarp(&l);
	res = compare_flow(&l, ek, r_ek);
	print_paths(&l, res->tpath, res);
	write(1, "\n", 1);
	enter_ants(&l);
	free_final(&l, ek, r_ek);
	return (0);
}
