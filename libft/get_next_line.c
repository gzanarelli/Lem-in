/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: sifouche <marvin@le-101.fr>                +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/07 17:13:01 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2018/10/19 23:57:05 by sifouche    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

int		get_next_line(const int fd, char **line)
{
	int				res;
	char			buf[BUFF_SIZE + 1];
	static t_fdstr	*list = NULL;
	t_fdstr			*last_read;

	if (!line || fd < 0 || fd == 1 || !(*line = ft_memalloc(1)))
		return (-1);
	list = (!list) ? overread_manager(NULL, -2, "", OVERREAD_INIT) : list;
	res = 1;
	if ((last_read = overread_manager(list, fd, buf, OVERREAD_GET)) != NULL)
	{
		res = check_line_ended(list, ft_strcpy(buf, last_read->str), fd, -2);
		*line = ft_realloc((void *)*line, ft_strlen(*line) * sizeof(char) + 1,
				(ft_strlen(*line) + ft_strlen(buf)) * sizeof(char) + 1);
		res = (*line && ft_strcpy(*line, buf)) ? res : -1;
		ftgnl_lstdel(list, last_read);
	}
	while (!(res <= 0) && (res = read(fd, buf, BUFF_SIZE)) > 0)
	{
		res = check_line_ended(list, buf, fd, res);
		*line = ft_realloc((void *)*line, ft_strlen(*line) * sizeof(char) + 1,
				(ft_strlen(*line) + ft_strlen(buf)) * sizeof(char) + 1);
		res = (*line && ft_strcat(*line, buf)) ? res : -1;
	}
	return ((res != -1) ? (ft_strlen(*line) > 0 || res == -2) : res);
}

int		check_line_ended(t_fdstr *list, char buf[BUFF_SIZE + 1],
			int fd, int res)
{
	int i;

	i = 0;
	buf[BUFF_SIZE] = '\0';
	if (res >= 0)
		buf[res] = '\0';
	while (i < BUFF_SIZE)
	{
		if (buf[i] == '\n')
		{
			if (i < BUFF_SIZE - 1 && buf[i + 1] != '\0' && buf[i + 1] != 26)
				overread_manager(list, fd, &buf[i + 1], OVERREAD_ADD);
			buf[i] = '\0';
			return (-2);
		}
		if (buf[i] == 26 || buf[i] == '\0')
		{
			buf[i] = '\0';
			if (res == -2)
				return (1);
			return (0);
		}
		i++;
	}
	return (1);
}

t_fdstr	*overread_manager(t_fdstr *list, int fd,
		char str[BUFF_SIZE + 1], int flag)
{
	if (flag == OVERREAD_INIT)
		return (ftgnl_lstnew(-1, NULL));
	else if (flag == OVERREAD_GET)
	{
		while (list != NULL)
		{
			if (list->fd == fd)
				return (list);
			list = list->next;
		}
		return (NULL);
	}
	else if (flag == OVERREAD_ADD)
	{
		while (list->next != NULL)
			list = list->next;
		list->next = ftgnl_lstnew(fd, str);
		return (NULL);
	}
	return (NULL);
}

t_fdstr	*ftgnl_lstnew(int fd, char str[BUFF_SIZE])
{
	t_fdstr *new;

	new = malloc(sizeof(*new));
	if (new == NULL)
		return (NULL);
	new->next = NULL;
	new->fd = fd;
	if (fd >= 0)
		ft_strcpy(new->str, str);
	new->str[BUFF_SIZE] = '\0';
	return (new);
}

void	ftgnl_lstdel(t_fdstr *list, t_fdstr *tofree)
{
	t_fdstr *last;

	last = NULL;
	while (list != NULL)
	{
		if (list == tofree)
		{
			last->next = list->next;
			list = NULL;
			free(tofree);
		}
		else
		{
			last = list;
			list = list->next;
		}
	}
}
