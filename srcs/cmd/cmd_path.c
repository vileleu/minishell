/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vileleu <vileleu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 16:22:13 by vileleu           #+#    #+#             */
/*   Updated: 2020/10/27 17:34:33 by vileleu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		where_path(char **path, char *s)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != ':')
		i++;
	if (i == 0)
		return (0);
	if (!(*path = malloc(sizeof(char) * (i + 1))))
		return (-1);
	i = 0;
	while (s[i] != ':')
	{
		(*path)[i] = s[i];
		i++;
	}
	(*path)[i] = '\0';
	return (i);
}

char	*find_path(char *s)
{
	char	*path;
	int		ret;
	int		i;

	i = 0;
	while ((ret = where_path(&path, s + i)) > 0)
	{
		
		i += ret;
	}
}

char	*cmd_path(t_o *o)
{
	t_list	*tmp;

	tmp = o->ev;
	while (tmp)
	{
		if (ft_strcmp_eg(tmp->content, "PATH") == 0)
		{
			if (!(find_path(tmp->content)))
		}
		tmp = tmp->next;
	}
}
