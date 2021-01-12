/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 14:41:47 by vileleu           #+#    #+#             */
/*   Updated: 2021/01/12 13:20:23 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

/*
** renvoie la commande vers la bonne fonction
*/

char	*commandes(t_o *o)
{
	if (ft_strncmp(o->cmd[0], "cd", 3) == 0)
		return (cmd_cd(o));
	else if (ft_strncmp(o->cmd[0], "echo", 5) == 0)
		return (cmd_echo(o));
	else if (ft_strncmp(o->cmd[0], "pwd", 4) == 0)
		return (cmd_pwd(o));
	else if (ft_strncmp(o->cmd[0], "env", 4) == 0)
		return (cmd_env(o));
	else if (ft_strncmp(o->cmd[0], "export", 7) == 0)
		return (cmd_export(o));
	else if (ft_strncmp(o->cmd[0], "unset", 6) == 0)
		return (cmd_unset(o));
	else if (ft_strncmp(o->cmd[0], "exit", 5) == 0)
		return (cmd_exit(o));
	else if (cmd_path(o) == 2)
		return ("?=0");
	else
		return (unknown(o));
}

int		work_in(t_o *o, char **line, int n)
{
	int		vide;

	o->fd = 1;
	vide = 0;
	if (!(verif_cmd(*line)))
		vide = 1;
	if (!(o->cmd = ft_split_m(line, ' ', o)))
		return (0);
	if (vide && o->cmd[1] == NULL && !ft_strcmp(o->cmd[0], ""))
		return (free_all(&(o->cmd), NULL, 1));
	if (o->cmd[0] == NULL)
	{
		o->cmd[0] = ft_strdup("");
		o->cmd[1] = NULL;
	}
	if (!(o->ret = commandes(o)))
		return (free_all(&(o->cmd), &(o->out), 0));
	if (n)
		return (free_all(&(o->cmd), NULL, 1));
	ft_putstr(o->out);
	if (o->fd)
		ft_putstr_fd("\n", o->fd);
	return (free_all(&(o->cmd), &(o->out), 1));
}

/*
** affichage par defaut du shell et parsing de l'entree std
*/

char	*loop(char *s, char **ev)
{
	char	*line;
	t_o		o;

	if (!(init_o(&o, s, ev)))
		return (error_leave("malloc failed", o, NULL));
	line = NULL;
	while (o.exit)
	{
		signal(SIGINT, sigint_signal);
		signal(SIGQUIT, sigquit_signal);
		PROMPT = 1;
		put_name(o.name, ": ", 1);
		if ((get_next_line(0, &line)) < 0)
			return (error_leave("malloc failed", o, line));
		if (verif_line(line) != 0)
		{
			if (!(parsing_work(&line, &o)))
				return (error_leave("malloc failed", o, line));
		}
		free(line);
	}
	return (NULL);
}

int		main(int ac, char **av, char **ev)
{
	if (ac != 1)
		return (error_leave_int("too many arguments", NULL));
	(void)av;
	PARENT_PID = getpid();
	loop("minishell", ev);
	return (0);
}
