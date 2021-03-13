/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 16:22:13 by vileleu           #+#    #+#             */
/*   Updated: 2021/03/10 15:54:28 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*free_all_char(char ***cmd, char **out, char *ret)
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

char	*error_rel(t_o *o, char *m, int n)
{
	o->out = ft_strdup("");
	o->fd = 2;
	ft_putstr_fd(o->name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(o->cmd[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(m, 2);
	return (ret_exit(n));
}

char	*error_errno_rel(t_o *o)
{
	int		n;

	ft_putstr_fd(o->name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(o->cmd[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	o->fd = 2;
	o->out = ft_strdup("");
	n = 126;
	if (errno == 2)
		n = 127;
	return (ret_exit(n));
}

void	error_exec(t_o *o, char *cmd)
{
	close(o->pipe[0]);
	write(o->pipe[1], "126", 3);
	close(o->pipe[1]);
	ft_putstr_fd(o->name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	exit(EXIT_FAILURE);
}
