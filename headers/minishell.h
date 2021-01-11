/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 15:33:30 by vileleu           #+#    #+#             */
/*   Updated: 2021/01/11 15:31:42 by thoberth         ###   ########.fr       */
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
# include "signal.h"
# include "../srcs/libft/libft.h"

int				PARENT_PID;
int				PROMPT;

typedef struct	s_o
{
	t_list		*ev;
	char		**cmd;
	char		*out;
	char		*name;
	char		*ret;
	int			fd;
	int			exit;
	int			i;
	int			len;
}				t_o;

/*
** fonctions d'erreurs
*/

char			*error_leave(char *s, t_o o, char *line);
int				error_leave_int(char *s, char *line);
char			*error_errno(t_o *o);
char			*error_arg(t_o *o);
char			*error_env(t_o *o, char *msg);
char			*error_syntx(t_o *o, char *msg, char *ret);
char			*error_spe(t_o *o, char *cmd);
char			*error_mine(t_o *o, char *msg);
int				big_free(char **s1, char **s2);

/*
** fonctions de commandes
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

int				work_in(t_o *o, char **line, int n);

/*
** commande export
*/

int				is_egual(char *s);
char			*print_ev(t_o *o);
char			**sort(t_o *o, char **cmd, int j, t_list *temp);
void			ft_swap(char **s1, char **s2);

/*
** fonctions parsing
*/

char			*ev_pars(char *line, t_o *o);
int				parsing_work(char **line, t_o *o);
char			*quote(char *line);
int				verif_line(char *line);
int				ev_strdup(char **line, int *i, t_o *o, int v);
char			**ft_split_m(char **s, char c, t_o *o);
int				size_ev(char *s, t_o *o, int v);

/*
** fonctions ev
*/

int				ft_strlen_ev(char *s);
int				loop_split_ev_bis(char **s, char *str, int *size, t_o *o);

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

#endif
