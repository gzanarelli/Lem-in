/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   utils.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/02 12:56:08 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/04 15:06:35 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"

void	exit_err(char *msg)
{
	perror(msg);
	exit(1);
}

void	free_edkarp(t_lem *l, t_edkarp *ek)
{
	int i;

	i = 0;
	while (i < l->nbrooms)
	{
		free(ek->tpath[i]);
		i++;
	}
	free(ek->tpath);
	free(ek->tparent);
	free(ek);
}

void	free_lem(t_lem *l)
{
	int i;

	i = 0;
	while (i < l->nbrooms)
	{
		free(l->map[i]);
		i++;
	}
	free(l->map);
	i = 0;
	while (i < l->nbrooms)
	{
		free(l->matrix[i]);
		i++;
	}
	free(l->matrix);
}

void	free_paths(t_lem *l)
{
	int j;
	int i;

	i = 0;
	while (i < l->nb_path)
	{
		j = 0;
		while (1)
		{
			if (l->tab_path[i].path[j][0] == l->end)
				break ;
			free(l->tab_path[i].path[j]);
			j++;
		}
		free(l->tab_path[i].path[j]);
		free(l->tab_path[i].path);
		i++;
	}
	free(l->tab_path);
}

void	free_final(t_lem *l, t_edkarp *ek, t_edkarp *r_ek)
{
	free_edkarp(l, ek);
	free_edkarp(l, r_ek);
	free_lem(l);
	free_paths(l);
}
