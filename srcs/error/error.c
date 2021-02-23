/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vileleu <vileleu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 15:54:39 by vileleu           #+#    #+#             */
/*   Updated: 2021/02/23 17:19:25 by vileleu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*error_leave(char *s, t_o *o, char *line)
{
	t_list	*tmp;

	if (line != NULL)
		free(line);
	while (o->ev)
	{
		tmp = o->ev;
		o->ev = o->ev->next;
		free(tmp->content);
		free(tmp);
	}
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", 2);
	return (NULL);
}

int		error_leave_int(char *s, char *line)
{
	if (line != NULL)
		free(line);
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", 2);
	return (0);
}

char	*error_errno(t_o *o)
{
	ft_putstr_fd(o->name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(o->cmd[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(o->cmd[1], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	o->fd = 2;
	o->out = ft_strdup("");
	return ("?=1");
}

char	*error_arg(t_o *o)
{
	ft_putstr_fd(o->name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(o->cmd[0], 2);
	ft_putstr_fd(": too many arguments", 2);
	o->fd = 2;
	o->out = ft_strdup("");
	return ("?=1");
}

char	*error_spe(t_o *o, char *cmd)
{
	ft_putstr_fd(o->name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(o->cmd[0], 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd("': not a valid identifier", 2);
	o->fd = 2;
	return ("?=1");
}
