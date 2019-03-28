/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_mgr.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/31 14:10:03 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/04 16:20:03 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"

static void	creatematrix(t_lem *l)
{
	int i;
	int j;

	l->matrix = malloc(sizeof(int *) * l->nbrooms);
	if (l->matrix == NULL)
		exit_err("Malloc error on matrix (dim 1) init\n");
	i = 0;
	while (i < l->nbrooms)
	{
		l->matrix[i] = malloc(sizeof(int) * l->nbrooms);
		if (l->matrix == NULL)
			exit_err("Malloc error on matrix (dim 2) init\n");
		j = 0;
		while (j < l->nbrooms)
		{
			l->matrix[i][j] = 0;
			j++;
		}
		i++;
	}
}

static void	createmap(t_lem *l, t_roomq *rq)
{
	int i;

	l->map = malloc(sizeof(char *) * l->nbrooms);
	if (l->map == NULL)
		exit_err("Malloc error on rooms map init\n");
	i = 0;
	while (rq && i < l->nbrooms)
	{
		if (rq->special == 1)
			l->start = i;
		else if (rq->special == 2)
			l->end = i;
		l->map[i] = rq->name;
		roomq_del_first(&rq);
		i++;
	}
}

static int	parse_rooms(t_lem *l, t_line *ln)
{
	int		isroom;
	int		special;
	t_roomq	*rq;

	rq = NULL;
	isroom = 1;
	special = readline(ln);
	while (special >= 0 && isroom == 1 && ln->line[0] != '\0')
	{
		if (special > 0)
			readline(ln);
		if (isroom == 1)
			isroom = get_room(l, ln->line, special, &rq);
		if (isroom == 1)
			special = readline(ln);
	}
	createmap(l, rq);
	creatematrix(l);
	return (isroom);
}

void		parse_map(t_lem *l)
{
	t_line	ln;
	int		stop;

	init_line(&ln);
	stop = 1;
	if (readline(&ln) != -1 && get_ants(l, ln.line))
		stop = parse_rooms(l, &ln);
	while (stop == 0 && ln.line[0] != '\0')
	{
		stop = get_link(l, ln.line);
		if (readline(&ln) == -1)
			break ;
	}
	free(ln.line);
}
