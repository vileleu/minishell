/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 14:36:07 by vileleu           #+#    #+#             */
/*   Updated: 2021/01/12 13:18:59 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*cmd_pwd(t_o *o)
{
	if (!(o->out = getcwd(NULL, 0)))
		return (error_errno(o));
	return ("?=0");
}

char	*cmd_echo(t_o *o)
{
	int		i;

	i = 1;
	if (o->cmd[i] && ft_strncmp(o->cmd[i], "-n", 3) == 0 && i++)
		o->fd = 0;
	o->out = ft_strdup("");
	while (o->cmd[i])
	{
		if ((i == 1 && o->fd == 1) || (i == 2 && o->fd == 0))
		{
			if (!(o->out = ft_strjoin(o->out, o->cmd[i])))
				return (NULL);
		}
		else
		{
			if (!(o->out = ft_strjoin_sp(o->out, o->cmd[i], ' ')))
				return (NULL);
		}
		i++;
	}
	return ("?=0");
}

char	*unknown(t_o *o)
{
	ft_putstr_fd(o->name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(o->cmd[0], 2);
	ft_putstr_fd(": command not found", 2);
	o->fd = 2;
	o->out = ft_strdup("");
	return ("?=127");
}

char	*cmd_exit(t_o *o)
{
	t_list	*tmp;

	o->exit = 0;
	o->fd = 0;
	o->out = ft_strdup("");
	while (o->ev)
	{
		tmp = o->ev;
		o->ev = o->ev->next;
		free(tmp->content);
		free(tmp);
	}
	return ("?=255");
}
