/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vileleu <vileleu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 14:36:07 by vileleu           #+#    #+#             */
/*   Updated: 2021/02/23 16:41:26 by vileleu          ###   ########.fr       */
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
	while (o->cmd[i] && ft_strncmp(o->cmd[i], "-n", 3) == 0 && i++)
		o->fd = 0;
	o->out = ft_strdup("");
	while (o->cmd[i])
	{
		if (i == 1 || !ft_strncmp(o->cmd[i - 1], "-n", 3))
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
	int		nb;
	int		i;

	nb = 0;
	ft_putstr_fd("exit\n", 2);
	if (o->cmd[1] && o->cmd[2] && full_digit(o->cmd[1]))
		return (error_arg(o));
	else if (o->cmd[1] && !full_digit(o->cmd[1]))
		return (error_exit(o));
	else if (o->cmd[1] && full_digit(o->cmd[1]))
	{
		i = 0;
		while (o->cmd[1][i])
		{
			if (i == 0 && o->cmd[1][i] == '-')
				i++;
			nb = nb * 10 + o->cmd[1][i] - '0';
			i++;
		}
		if (full_digit(o->cmd[1]) < 0)
			nb = -1 * nb + 256;
	}
	o->fd = 0;
	del_ev_exit(o);
	return (ret_exit(nb % 256));
}
