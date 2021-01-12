/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_ev.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 16:16:19 by vileleu           #+#    #+#             */
/*   Updated: 2021/01/12 13:19:02 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*cmd_env(t_o *o)
{
	t_list	*tmp;

	tmp = o->ev;
	o->out = ft_strdup("");
	while (tmp)
	{
		if (is_egual(tmp->content) >= 0 && strncmp(tmp->content, "", 1) != 0)
		{
			if (strncmp(o->out, "", 1) == 0)
			{
				if (!(o->out = ft_strjoin(o->out, tmp->content)))
					return (NULL);
			}
			else
			{
				if (!(o->out = ft_strjoin_sp(o->out, tmp->content, '\n')))
					return (NULL);
			}
		}
		tmp = tmp->next;
	}
	if (ft_strcmp(o->out, "") == 0 || o->cmd[1] != NULL)
		return (error_env(o, "No such file or directory"));
	return ("?=0");
}

char	*export_replace_bis(t_list *tmp, char *cmd, int w)
{
	if (cmd[w - 1] == '+' && is_egual(tmp->content) >= 0)
	{
		if (!(tmp->content = ft_strjoin(tmp->content, cmd + w + 1)))
			return (NULL);
	}
	else if (cmd[w - 1] == '+' && is_egual(tmp->content) == -1)
	{
		if (!(tmp->content = ft_strjoin_sp(tmp->content, cmd + w + 1, '=')))
			return (NULL);
	}
	else
	{
		free(tmp->content);
		if (!(tmp->content = ft_strdup(cmd)))
			return (NULL);
	}
	return (tmp->content);
}

char	*export_replace(t_o *o, char **cmd, int w)
{
	t_list	*tmp;
	char	*rep;

	tmp = o->ev;
	rep = "?=0";
	while (tmp)
	{
		if ((w = is_egual(*cmd)) > 0 && ft_strcmp_eg(tmp->content, *cmd) == 0)
		{
			if (!(tmp->content = export_replace_bis(tmp, *cmd, w)))
				return (NULL);
			rep = "?=2";
		}
		if (w == -1 && ft_strcmp_eg(tmp->content, *cmd) == 0)
			return ("?=2");
		tmp = tmp->next;
	}
	if (ft_strcmp(rep, "?=0") == 0 && w > 0 && (*cmd)[w - 1] == '+')
		*cmd = modif_str(*cmd);
	return (rep);
}

char	*export_verif(t_o *o, char **cmd)
{
	int		i;

	i = 0;
	while ((*cmd)[i])
	{
		if ((((*cmd)[i] == '+' && (*cmd)[i + 1] == '=') || \
		(*cmd)[i] == '=') && i > 0)
			break ;
		if ((*cmd)[i] == '=' && i == 0)
			return (error_spe(o, *cmd));
		if (((*cmd)[i] < 'a' || (*cmd)[i] > 'z') && ((*cmd)[i] < 'A' \
		|| (*cmd)[i] > 'Z') && (*cmd)[i] != '_' && i == 0)
			return (error_spe(o, *cmd));
		if (((*cmd)[i] < 'a' || (*cmd)[i] > 'z') && ((*cmd)[i] < 'A' || \
		(*cmd)[i] > 'Z') && ((*cmd)[i] < '0' || (*cmd)[i] > '9') && \
		(*cmd)[i] != '_')
			return (error_spe(o, *cmd));
		i++;
	}
	if (i == 0)
		return (error_spe(o, *cmd));
	return (export_replace(o, cmd, -1));
}

char	*cmd_export(t_o *o)
{
	t_list	*tmp;
	char	*ret;
	char	*prev;
	int		i;

	ret = "?=0";
	if (!o->cmd[1])
		return (print_ev(o));
	o->fd = 0;
	i = 1;
	while (o->cmd[i])
	{
		prev = export_verif(o, &o->cmd[i]);
		if (ft_strcmp(prev, "?=1") == 0 && ft_strcmp(ret, "?=0") == 0)
			ret = "?=1";
		if (ft_strcmp(prev, "?=0") == 0)
		{
			tmp = ft_lstnew(ft_strdup(o->cmd[i]));
			ft_lstadd_back(&o->ev, tmp);
		}
		i++;
	}
	o->out = ft_strdup("");
	return (ret);
}
