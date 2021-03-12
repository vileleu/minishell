/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_rel.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 16:22:13 by vileleu           #+#    #+#             */
/*   Updated: 2021/03/10 15:54:28 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int		there_is_slash(t_o *o)
{
	int		i;

	i = 0;
	while (o->cmd[0][i])
	{
		if (o->cmd[0][i] == '/')
			return (1);
		i++;
	}
	return (0);
}

char	*create_path(char *cmd, int i)
{
	char	*s;
	int		j;

	if (!(s = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	j = -1;
	while (++j < i)
		s[j] = cmd[j];
	s[j] = '\0';
	return (s);
}

char	*create_exe(t_o *o, char **path, int len)
{
	char	*s;
	int		i;
	int		max;

	i = ft_strlen(o->cmd[0]) - 1;
	max = i + 1;
	while (i >= 0)
	{
		if (o->cmd[0][i] == '/' && len)
			break ;
		if (o->cmd[0][i] == '/' && !len--)
			max = i;
		i--;
		len++;
	}
	if (!(*path = create_path(o->cmd[0], i + 1)))
		return (NULL);
	if (!(s = malloc(sizeof(char) * (len + 1))))
		return (free_char(path, NULL));
	len = 0;
	while (o->cmd[0][++i] && i < max)
		s[len++] = o->cmd[0][i];
	s[len] = '\0';
	return (s);
}

char	**make_cpy(t_o *o, char *cmd, int i)
{
	char	**cpy;
	int		len;
	int		j;
	int		k;

	i = 0;
	while (o->cmd[i])
		i++;
	if (!(cpy = malloc(sizeof(char*) * (i + 1))))
		return (NULL);
	if (!(cpy[0] = ft_strdup(cmd)))
		return (free_tab(cpy, -1));
	j = 0;
	while (++j < i)
	{
		if (!(cpy[j] = malloc(sizeof(char) * (ft_strlen(o->cmd[j]) + 1))))
			return (free_tab(cpy, i - 1));
		k = -1;
		len = ft_strlen(o->cmd[j]);
		while (++k < len)
			cpy[j][k] = o->cmd[j][k];
		cpy[j][k] = '\0';
	}
	cpy[j] = NULL;
	return (cpy);
}

char	*cmd_rel(t_o *o)
{
	char	**cpy;
	char	*cmd;
	char	*path;
	int		ret;

	o->fd = 0;
	if (!(cmd = create_exe(o, &path, 0)))
		return (NULL);
	if (!(cpy = make_cpy(o, cmd, 0)))
		return (free_char(&cmd, &path));
	free(cmd);
	if ((ret = open(o->cmd[0], O_RDWR)) == -1)
	{
		free_all_char(&cpy, &path, NULL);
		return (error_errno_rel(o));
	}
	close(ret);
	if (!(find_exe(&path, cpy, o)))
		return (free_all_char(&cpy, &path, NULL));
	free_all_char(&cpy, &path, NULL);
	return ("?=0");
}
