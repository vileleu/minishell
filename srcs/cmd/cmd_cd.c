/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 14:36:07 by vileleu           #+#    #+#             */
/*   Updated: 2020/12/03 21:57:31 by vico             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_home(t_o *o)
{
	t_list	*tmp;
	char	*ret;

	ret = NULL;
	tmp = o->ev;
	while (tmp)
	{
		if (ft_strcmp_eg(tmp->content, "HOME") == 0)
		{
			ret = ft_strdup(tmp->content + 5);
			break ;
		}
		tmp = tmp->next;
	}
	return (ret);
}

char	*cmd_cd(t_o *o)
{
	char	*tmp;

	o->fd = 0;
	if (o->cmd[1] == NULL)
	{
		if ((tmp = find_home(o)) == NULL)
			return (error_mine(o, "HOME not set"));
		if ((chdir(tmp)) < 0)
			return (error_errno(o));
		free(tmp);
		o->out = ft_strdup("");
		return ("?=0");
	}
	if ((chdir(o->cmd[1])) < 0)
		return (error_errno(o));
	o->out = ft_strdup("");
	return ("?=0");
}