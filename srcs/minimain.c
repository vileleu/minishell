/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimain.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vileleu <vileleu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 14:41:47 by vileleu           #+#    #+#             */
/*   Updated: 2021/03/09 15:22:58 by vileleu          ###   ########.fr       */
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
		return (o->ret);
	else
		return (unknown(o));
}

int		work_in(t_o *o, char **line)
{
	int		ret;

	o->fd = 1;
	if (!(ret = redirections(o, line)))
		return (0);
	else if (ret == -1)
		return (1);
	if (!ft_strcmp(*line, ""))
		return (1);
	if (!(o->cmd = ft_split_m(line, ' ', o)))
		return (0);
	if (o->cmd[0] == NULL)
		return (free_all(&(o->cmd), NULL, 1));
	if (o->cmd[0] == NULL)
	{
		o->cmd[0] = ft_strdup("");
		o->cmd[1] = NULL;
	}
	if (!(o->ret = commandes(o)))
		return (free_all(&(o->cmd), &(o->out), 0));
	ft_putstr(o->out);
	if (o->fd)
		ft_putstr_fd("\n", o->fd);
	return (free_all(&(o->cmd), &(o->out), 1));
}

/*
** affichage par defaut du shell et parsing de l'entree std
*/

char	*second_loop(t_o *o, char *line, int ret)
{
	put_name(o->name, ": ", 2);
	if ((ret = get_next_line(0, &line)) < 0)
		return (error_leave("malloc failed", o, line));
	if (in_fork)
	{
		if (in_fork == 130)
			o->ret = "?=130";
		in_fork = 0;
	}
	if (!ret && !ft_strcmp(line, ""))
	{
		free(line);
		line = ft_strdup("exit");
	}
	if (verif_line(line) != 0)
	{
		if (!(parsing_work(&line, o)))
			return (error_leave("malloc failed", o, line));
	}
	free(line);
	return ("");
}

char	*loop(char *s, char **ev)
{
	char	*line;
	int		ret;
	t_o		o;

	ret = 0;
	if (!(init_o(&o, s, ev)))
		return (NULL);
	line = NULL;
	while (o.exit)
	{
		if (!(second_loop(&o, line, ret)))
			return (NULL);
	}
	return (NULL);
}

int		main(int ac, char **av, char **ev)
{
	if (ac != 1)
		return (error_leave_int("too many arguments", NULL));
	(void)av;
	in_fork = 0;
	signal(SIGINT, sigint_signal);
	signal(SIGQUIT, sigquit_signal);
	loop("minishell", ev);
	return (0);
}
