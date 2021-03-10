/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 17:49:51 by vileleu           #+#    #+#             */
/*   Updated: 2021/03/10 15:53:03 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int		free_twice(char ***cmd, t_pipe *tuy, int ret)
{
	int		i;

	i = 0;
	if (cmd != NULL)
	{
		while ((*cmd)[i])
			free((*cmd)[i++]);
		free(*cmd);
	}
	if (tuy != NULL)
		free_pipe(tuy);
	return (ret);
}

char	*error_eof(char **line, char c, char join)
{
	if (g_fork - ((g_fork / 1000) * 1000) == 130 ||
		g_fork - ((g_fork / 1000) * 1000) == 131)
		return (*line);
	else if (join == '\n')
	{
		ft_putstr_fd("minishell: unexpected EOF while looking for matching `",
			2);
		ft_putchar_fd(c, 2);
		ft_putstr_fd("'\nminishell: syntax error: unexpected end of file\n", 2);
	}
	else if (join == ' ')
		ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
	else
	{
		free(*line);
		*line = ft_strdup("exit");
	}
	return (*line);
}

char	*free_char(char **str)
{
	if (*str)
		free(*str);
	return (NULL);
}

char	*error_errnoo(t_o *o, char *tmp)
{
	ft_putstr_fd(o->name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(o->cmd[0], 2);
	ft_putstr_fd(": ", 2);
	if (tmp)
	{
		ft_putstr_fd(tmp, 2);
		ft_putstr_fd(": ", 2);
		free(tmp);
	}
	ft_putstr_fd(strerror(errno), 2);
	o->fd = 2;
	o->out = ft_strdup("");
	return ("?=1");
}
