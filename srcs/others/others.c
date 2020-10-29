/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vileleu <vileleu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 16:17:10 by vileleu           #+#    #+#             */
/*   Updated: 2020/10/27 15:16:07 by vileleu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_name(char *s, char *sup, int fd)
{
	ft_putstr_fd("\033[0;35m", fd);
	ft_putstr_fd(s, fd);
	ft_putstr_fd(sup, fd);
	ft_putstr_fd("\033[0m", fd);
}

int		verif_line(char *line)
{
	int		i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\v' \
	|| line[i] == '\f' || line[i] == '\r')
		i++;
	if (line[i] == 0)
		return (0);
	else
		return (1);
}

int		init_o(t_o *o, char *name, char **ev)
{
	t_list	*tmp;
	int		i;

	i = 0;
	o->cmd = NULL;
	o->name = name;
	o->out = NULL;
	o->fd = 1;
	o->ret = "?=0";
	o->exit = 1;
	o->i = 0;
	o->len = 0;
	if (!(o->ev = ft_lstnew(ft_strdup(ev[i++]))))
		return (0);
	tmp = o->ev;
	while (ev[i])
	{
		if (!(tmp->next = ft_lstnew(ft_strdup(ev[i++]))))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

int		verif_cmd(char *cmd)
{
	int		i;

	i = 0;
	if (cmd[i++] == '$')
	{
		while ((cmd[i] >= 'a' && cmd[i] <= 'z') || (cmd[i] >= 'A' && \
		cmd[i] <= 'Z') || (cmd[i] >= '0' && cmd[i] <= '9') || cmd[i] == '_')
		{
			if ((cmd[i] >= '0' && cmd[i] <= '9') && i == 0)
				return (1);
			i++;
		}
		if (cmd[i] == '\0')
			return (0);
	}
	return (1);
}
