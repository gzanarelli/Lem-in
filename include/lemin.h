/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lemin.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: gzanarel <gzanarel@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/12/20 14:33:18 by sifouche     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/04 15:31:16 by gzanarel    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H
# include "../libft/libft.h"
# include "../libft/ft_printf.h"

typedef struct		s_roomq
{
	int				special;
	char			*name;
	struct s_roomq	*next;
}					t_roomq;

typedef struct		s_line
{
	char			*line;
	int				size;
}					t_line;

typedef struct		s_edkarp
{
	int				flow;
	int				maxflow;
	int				*tflux;
	int				*tparent;
	int				**tpath;
}					t_edkarp;

typedef struct		s_queue
{
	int				val;
	struct s_queue	*next;
}					t_queue;

typedef struct		s_room
{
	int				id;
	char			*name;
}					t_room;

typedef struct		s_path
{
	int				size;
	int				ope;
	int				**path;
}					t_path;

typedef struct		s_lem
{
	int				ants;
	int				start;
	int				s_link;
	int				end;
	int				e_link;
	int				nb_path;
	int				stop;
	t_path			*tab_path;
	char			**map;
	t_edkarp		e;
	int				**matrix;
	int				max_flow;
	int				nbrooms;
}					t_lem;

/*
** queue
*/
void				queue_push(t_queue **q, int val);
void				queue_delete(t_queue **q);
int					queue_pop(t_queue **q);
void				queue_view(t_queue **q);

/*
** ed-karp
*/
t_edkarp			*edmondkarp(t_lem *l);
t_edkarp			*r_edmondkarp(t_lem *l);
int					bfs(t_lem *l, int **tpath, int *tparent);
int					r_bfs(t_lem *l, int **tpath, int *tparent);
t_edkarp			*compare_flow(t_lem *l, t_edkarp *ek, t_edkarp *r_ek);

/*
** save_paths
*/
void				print_paths(t_lem *l, int **tpath, t_edkarp *ek);

/*
** moove_ants
*/
void				enter_ants(t_lem *l);
void				moove_ants(t_lem *l);
int					verif_path(t_lem *l, int ants_tt, int ants, int i);

void				init_line(t_line *ln);
int					readline(t_line *ln);

void				exit_err(char *msg);

/*
** room // parse
*/
void				roomq_push(t_roomq **rq, int special, char *name);
void				roomq_delete(t_roomq **rq);
void				roomq_del_first(t_roomq **rq);

int					get_room(t_lem *l, char *line, int special, t_roomq **rq);
int					get_ants(t_lem *l, char *line);
int					get_link(t_lem *l, char *line);
void				parse_map(t_lem *l);

/*
** free
*/
void				free_edkarp(t_lem *l, t_edkarp *ek);
void				free_lem(t_lem *l);
void				free_paths(t_lem *l);
void				free_final(t_lem *l, t_edkarp *ek, t_edkarp *r_ek);

#endif
