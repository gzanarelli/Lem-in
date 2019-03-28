/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_room.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/31 11:06:24 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/04 14:41:37 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"

static int	check_valid_room(char *line)
{
	int spaces;
	int i;

	if (line[0] == 'L')
		return (-1);
	spaces = 0;
	i = 0;
	while (line[i] != '\0' && line[i] != ' ')
	{
		if (line[i] == '-')
			return (0);
		i++;
	}
	while (i > 0 && line[i] != '\0')
	{
		if (line[i] == ' ' && line[i + 1] != '\0')
			spaces++;
		else if (line[i] == '-' && !(line[i + 1] >= '0' && line[i + 1] <= '9'))
			return (-1);
		else if (line[i] != '-' && !(line[i] >= '0' && line[i] <= '9'))
			return (-1);
		i++;
	}
	return (spaces != 2 ? -1 : 1);
}

static char	*get_room_name(char *line)
{
	char	*name;
	int		size;

	size = ft_strlen_c(line, ' ');
	line[size] = '\0';
	name = ft_strdup(line);
	if (name == NULL)
		exit_err("Malloc error on parse_room : Name is NULL.\n");
	return (name);
}

int			get_room(t_lem *l, char *line, int special, t_roomq **rq)
{
	char	*name;
	int		valid;

	valid = check_valid_room(line);
	if (valid)
	{
		name = get_room_name(line);
		l->nbrooms++;
		roomq_push(rq, special, name);
	}
	return (valid);
}
