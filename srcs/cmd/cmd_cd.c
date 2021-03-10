/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 14:36:07 by vileleu           #+#    #+#             */
/*   Updated: 2021/02/22 10:08:51 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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

char	*fill(int len, char *pwd, char *name)
{
	char	*new;
	int		i;
	int		j;

	if (!(new = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	i = -1;
	while (++i < len - (int)ft_strlen(pwd) - 1)
		new[i] = name[i];
	new[i++] = '=';
	j = -1;
	while (++j < (int)ft_strlen(pwd))
		new[i + j] = pwd[j];
	new[i + j] = '\0';
	free(pwd);
	return (new);
}

int		pwd_old(t_o *o, char *name)
{
	t_list	*tmp;
	char	*pwd;
	char	*new;
	int		len;

	tmp = o->ev;
	while (tmp)
	{
		if (ft_strcmp_eg(tmp->content, name) == 0)
		{
			if (!(pwd = getcwd(NULL, 0)))
				return (0);
			len = ft_strlen(pwd) + ft_strlen(name) + 1;
			if (!(new = fill(len, pwd, name)))
				return (0);
			free(tmp->content);
			if (!(tmp->content = ft_strdup(new)))
				return (0);
			free(new);
			break ;
		}
		tmp = tmp->next;
	}
	return (1);
}

char	*multiple(t_o *o)
{
	if (!(pwd_old(o, "OLDPWD")))
		return (error_errno(o));
	if ((chdir(o->cmd[1])) < 0)
		return (error_errno(o));
	if (!(pwd_old(o, "PWD")))
		return (error_errno(o));
	o->out = ft_strdup("");
	return ("?=0");
}

char	*cmd_cd(t_o *o)
{
	char	*tmp;

	o->fd = 0;
	if (o->cmd[1] == NULL)
	{
		if ((tmp = find_home(o)) == NULL)
			return (error_mine(o, "HOME not set"));
		if (!(pwd_old(o, "OLDPWD")))
			return (error_errno(o));
		if ((chdir(tmp)) < 0)
			return (error_errnoo(o, tmp));
		if (!(pwd_old(o, "PWD")))
			return (error_errno(o));
		free(tmp);
		o->out = ft_strdup("");
		return ("?=0");
	}
	return (multiple(o));
}
