/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parse_ants.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/31 15:07:35 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/04 14:36:50 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"

static int	check_valid_ants(char *line)
{
	int i;

	i = 0;
	while (line[i] != '\0')
	{
		if (!(line[i] >= '0' && line[i] <= '9'))
			return (0);
		i++;
	}
	if (ft_strlen(line) > 10 || (ft_strlen(line) == 10 && line[0] > '2'))
		return (0);
	return (1);
}

int			get_ants(t_lem *l, char *line)
{
	l->ants = ft_atoi(line);
	if (l->ants < 1 || !check_valid_ants(line))
	{
		l->ants = 0;
		return (0);
	}
	return (1);
}
