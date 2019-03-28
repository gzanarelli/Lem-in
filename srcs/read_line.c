/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   read_line.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/02 14:53:11 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/04 16:20:07 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"

static int	iscomment(char *line)
{
	if (line[0] == '#' && line[1] != '#')
		return (1);
	return (0);
}

static int	is_special(char *line)
{
	if (line[0] == '#' && line[1] == '#')
	{
		if (!ft_strcmp(line, "##start"))
			return (1);
		else if (!ft_strcmp(line, "##end"))
			return (2);
		else
			return (-1);
	}
	return (0);
}

static void	realloc_line(t_line *ln, int i)
{
	if (i >= ln->size)
	{
		ln->line = ft_realloc((void *)ln->line, ln->size, ln->size * 2);
		ln->size *= 2;
		if (ln->line == NULL)
			exit_err("Malloc error on line realloc");
	}
}

void		init_line(t_line *ln)
{
	ln->size = 256;
	ln->line = malloc(sizeof(char) * ln->size);
	if (ln->line == NULL)
		exit_err("Malloc error on line init");
}

int			readline(t_line *ln)
{
	int		i;
	char	buf[1];

	buf[0] = '\0';
	i = 0;
	if (read(0, buf, 1) <= 0)
		return (-1);
	while (buf[0] != '\n' && buf[0] != '\0')
	{
		ln->line[i] = buf[0];
		i++;
		realloc_line(ln, i);
		if (read(0, buf, 1) <= 0)
			break ;
	}
	ln->line[i] = '\0';
	ft_putendl(ln->line);
	if (iscomment(ln->line))
		readline(ln);
	return (is_special(ln->line));
}
