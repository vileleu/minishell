/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vileleu <vileleu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 15:33:30 by vileleu           #+#    #+#             */
/*   Updated: 2021/03/08 15:03:29 by vileleu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BUF 1

# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <string.h>
# include <errno.h>
# include <dirent.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include "../srcs/libft/libft.h"

int				in_fork;

typedef struct	s_pipe
{
	int				fd[2];
	struct s_pipe	*next;
}				t_pipe;

typedef struct	s_o
{
	t_list		*ev; // liste des var env
	char		**cmd; // tableau de string des cmd ex : "echo" "$home"
	char		*out; // ce qu'on doit afficher ex = echo text, out = "text"
	char		*name; //sert a rien, stock le prompt
	char		*ret; // contient la valeur de la var d'env $?
	int			fd; // savoir si c'est une erreur ou pas pour le \n
	int			exit; // declarer a 1 a l'initialisation, while != 0 prog continue
	int			i; // reussir a mettre a la norme
	int			len; // reussir a mettre a la norme
	int			savout;
	int			savin;
	int			red_out;
	int			red_in;
}				t_o;

/*
** fonctions d'erreurs
*/

char			*error_leave(char *s, t_o *o, char *line);
int				error_leave_int(char *s, char *line);
char			*error_errno(t_o *o);
char			*error_arg(t_o *o);
char			*error_env(t_o *o, char *msg);
char			*error_syntx(t_o *o, char *msg, char *ret);
char			*error_spe(t_o *o, char *cmd);
char			*error_mine(t_o *o, char *msg);
int				big_free(char **s1, char **s2);
int				free_twice(char ***cmd, t_pipe *tuy, int ret);
char			*error_eof(char **line, char c, char join);
char			*free_char(char **str);
int				error_open(t_o *o, char ***new, char **name);

/*
** fonctions builtins
*/

char			*cmd_cd(t_o *o);
char			*cmd_echo(t_o *o);
char			*cmd_pwd(t_o *o);
char			*cmd_exit(t_o *o);
char			*cmd_env(t_o *o);
char			*cmd_export(t_o *o);
char			*cmd_unset(t_o *o);
int				cmd_path(t_o *o);
char			*unknown(t_o *o);

/*
** traitement de(s) commande(s)
*/

int				work_in(t_o *o, char **line);

/*
** commande export
*/

int				is_egual(char *s);
char			*print_ev(t_o *o);
char			**sort(t_o *o, int j, t_list *temp);
void			ft_swap(char **s1, char **s2);

/*
** fonctions parsing
*/

char			*ev_pars(char *line, t_o *o);
int				parsing_work(char **line, t_o *o);
char			*quote(char **line, int *ver);
int				verif_line(char *line);
int				ev_strdup(char **line, int *i, t_o *o, int v);
char			**ft_split_m(char **s, char c, t_o *o);
int				size_ev(char *s, t_o *o, int v);
int				parsing_char(t_o *o, char *line);
int				quote_bis(char **line, int *ver, char *c);
int				loop_quote(char **line, int *ver, char *c, int *i);
int				verif_slash(char *line, int i);
int				back_slash(char **line, int *ver, char *c, int *i);
void			quote_bbis(char *line, int *i, char c, int *comp);
int				is_quote(char *line ,int i, char m);
int				enter_quote(char *line, int i);

/*
** fonctions ev
*/

void			pour_la_norme(t_o *o, int *tmp, int j);
int				ft_strlen_ev(char *s);
int				loop_split_ev_bis(char **s, char *str, int *size, t_o *o);
void			delete_ev(t_o *o, char *str, int *i, int *nb);
void			delete_after(t_o *o, char *str, int *size);
char			*create_fake(char *line, int *i, int j, int v);
int				replace(char **line, int *i, char *s, t_o *o);
int				for_digit(t_o *o, char **line, int *i, int v);

/*
** fonctions pour les non builtins
*/

int				where_path(char **path, char *s);
char			**new_envp(t_o *o);

/*
** fonctions signaux
*/

void			sigquit_signal(int n);
void			sigint_signal(int n);
int				ret_signal(t_o *o);
char			*get_child(int *end);

/*
** fonctions pipe
*/

int				begin_pipe(t_o *o, char **pip, t_pipe **tuy, int n);
int				loop_pipe(t_o *o, char **pip, t_pipe **tuy, int i);
int				behind_pipe(char *line, int j, int stop, int *ver);
int				free_pipe(t_pipe *tuy);
int				init_pipe(char **pip, t_pipe **tuy);

/*
** fonctions redirections
*/

int				redirections(t_o *o, char **line);
int				where_redi(t_o *o, char **line, int beg, int end);
int				is_empty(char c);
void			close_all(t_o *o, int n);
void			ignore(char *line, int *i);
int				inc(char *line, int *beg);
char			*create_file_bis(char *line, int *beg, int *end, int *doub);
int				reset(t_o *o);

/*
** fonctions diverses
*/

char			*modif_str(char *s);
int				verif_cmd(char *cmd);
int				init_o(t_o *o, char *name, char **ev);
int				free_all(char ***cmd, char **out, int ret);
int				ft_strcmp_eg(char *s1, char *s2);
int				ft_strcmp_ev(char *s1, char *s2);
void			put_name(char *name, char *sup, int fd);
char			**free_tab(char **tab, int i);
void			return_child(t_o *o, int exit_pid);

#endif
