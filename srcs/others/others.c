/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 16:17:10 by vileleu           #+#    #+#             */
/*   Updated: 2021/01/12 13:19:24 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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
	o->savout = 0;
	if (!(ev[i]))
		return (1);
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
	int		ver;

	i = 0;
	ver = 1;
	if (cmd[i] == '\"' && ver++)
		i++;
	if (cmd[i++] == '$')
	{
		while ((cmd[i] >= 'a' && cmd[i] <= 'z') || (cmd[i] >= 'A' && \
		cmd[i] <= 'Z') || (cmd[i] >= '0' && cmd[i] <= '9') || cmd[i] == '_')
		{
			if ((cmd[i] >= '0' && cmd[i] <= '9') && i == 0)
				return (1);
			i++;
		}
		if (cmd[i] == '\"' && cmd[i + 1] == '\0' && ver == 2)
			return (0);
		if (cmd[i] == '\0')
			return (0);
	}
	return (1);
}

char	*modif_str(char *s)
{
	char	*new;
	int		i;
	int		j;

	if (!(new = malloc(sizeof(char) * ft_strlen(s))))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != '+')
			new[j++] = s[i++];
		else
			i++;
	}
	new[j] = '\0';
	free(s);
	return (new);
}
