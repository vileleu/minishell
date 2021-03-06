/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 17:49:51 by vileleu           #+#    #+#             */
/*   Updated: 2021/01/12 13:19:09 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*error_env(t_o *o, char *msg)
{
	if (ft_strcmp(o->out, "") == 0)
	{
		ft_putstr_fd(o->name, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(o->cmd[0], 2);
		ft_putstr_fd(": ", 2);
	}
	else if (o->cmd[1] != NULL)
	{
		ft_putstr_fd(o->cmd[0], 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(o->cmd[1], 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(msg, 2);
	o->fd = 2;
	return ("?=127");
}

char	*error_syntx(t_o *o, char *msg, char *ret)
{
	ft_putstr_fd(o->name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd(" `", 2);
	ft_putstr_fd(ret, 2);
	ft_putstr_fd("'\n", 2);
	return ("?=2");
}

int		free_all(char ***cmd, char **out, int ret)
{
	int		i;

	i = 0;
	if (cmd != NULL)
	{
		while ((*cmd)[i])
			free((*cmd)[i++]);
		free(*cmd);
	}
	if (out != NULL)
		free(*out);
	return (ret);
}

int		big_free(char **s1, char **s2)
{
	if (s1 != NULL)
		free(*s1);
	if (s2 != NULL)
		free(*s2);
	return (0);
}

char	*error_mine(t_o *o, char *msg)
{
	ft_putstr_fd(o->name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(o->cmd[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(msg, 2);
	o->fd = 2;
	o->out = ft_strdup("");
	return ("?=1");
}
