/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_link.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/31 15:34:58 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/04 14:39:13 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"

static int	add_link(t_lem *l, int ra, int rb)
{
	if (ra == -1 || rb == -1)
		return (0);
	l->matrix[ra][rb] = 1;
	l->matrix[rb][ra] = 1;
	if (ra == l->start || rb == l->start)
		l->s_link++;
	if (ra == l->end || rb == l->end)
		l->e_link++;
	return (1);
}

static int	get_room_id(t_lem *l, char *room, int dashpos)
{
	int		i;
	char	*name;

	if (dashpos > 0)
		name = ft_strsub(room, 0, dashpos);
	else
		name = room;
	if (name == NULL)
		exit_err("Malloc error on parse_link. Name is NULL.\n");
	i = 0;
	while (i < l->nbrooms)
	{
		if (!ft_strcmp(name, l->map[i]))
			break ;
		i++;
	}
	if (dashpos > 0)
		free(name);
	if (i < l->nbrooms)
		return (i);
	return (-1);
}

static int	check_valid_link(char *line)
{
	int	dashpos;
	int i;

	dashpos = -1;
	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '-')
		{
			if (dashpos != -1)
				return (0);
			dashpos = i;
		}
		i++;
	}
	if (dashpos < 1)
		return (0);
	return (dashpos);
}

int			get_link(t_lem *l, char *line)
{
	int valid;

	valid = check_valid_link(line);
	if (!valid)
		return (-1);
	valid = add_link(l, get_room_id(l, line, valid),
			get_room_id(l, &(line[valid + 1]), 0));
	if (!valid)
		return (-1);
	return (0);
}
