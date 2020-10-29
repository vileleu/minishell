/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_unset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vileleu <vileleu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 19:41:13 by vileleu           #+#    #+#             */
/*   Updated: 2020/10/24 19:37:30 by vileleu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_egual(char *s)
{
	int		i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	*unset_verif(t_o *o, char *cmd)
{
	int		i;

	i = 0;
	while (cmd[i])
	{
		if ((cmd[i] < 'a' || cmd[i] > 'z') && (cmd[i] < 'A' || \
		cmd[i] > 'Z') && cmd[i] != '_' && i == 0)
			return (error_spe(o, cmd));
		if ((cmd[i] < 'a' || cmd[i] > 'z') && (cmd[i] < 'A' || \
		cmd[i] > 'Z') && (cmd[i] < '0' || cmd[i] > '9') && cmd[i] != '_')
			return (error_spe(o, cmd));
		i++;
	}
	return ("?=0");
}

void	delete_maillon(t_o *o, char *cmd)
{
	t_list	*tmp;
	t_list	*prev;

	tmp = o->ev;
	if (ft_strcmp_eg(tmp->content, cmd) == 0)
	{
		o->ev = tmp->next;
		ft_lstdelone(tmp, &free);
		tmp = o->ev;
	}
	prev = tmp;
	while (tmp)
	{
		if (ft_strcmp_eg(tmp->content, cmd) == 0)
		{
			prev->next = tmp->next;
			ft_lstdelone(tmp, &free);
			tmp = prev;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

char	*cmd_unset(t_o *o)
{
	char	*prev;
	char	*ret;
	int		i;

	o->fd = 0;
	ret = "?=0";
	i = 0;
	while (o->cmd[++i])
	{
		prev = unset_verif(o, o->cmd[i]);
		if (ft_strcmp(prev, "?=0") == 0)
			delete_maillon(o, o->cmd[i]);
		if (ft_strcmp(prev, "?=1") == 0 && ft_strcmp(ret, "?=0") == 0)
			ret = "?=1";
	}
	o->out = ft_strdup("");
	return (ret);
}
