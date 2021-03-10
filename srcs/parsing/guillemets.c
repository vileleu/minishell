/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guillemets.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 15:11:21 by vileleu           #+#    #+#             */
/*   Updated: 2021/03/10 16:02:06 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*get_newline(char **line, int *ver, char c, char join)
{
	char	*newline;
	int		end;

	put_name("> ", "", 2);
	if (!(newline = get_child(&end)))
		return (NULL);
	if (!end || g_fork - ((g_fork / 1000) * 1000) == 130 ||
		g_fork - ((g_fork / 1000) * 1000) == 131)
	{
		*ver = 2;
		free(newline);
		return (error_eof(line, c, join));
	}
	if (join != '\0' && !(*line = ft_strjoin_sp(*line, newline, join)))
		return (NULL);
	else if (join == '\0')
	{
		free(*line);
		if (!(*line = ft_strdup(newline)))
			return (NULL);
	}
	free(newline);
	return (*line);
}

int		get_newpipe(char **line, int *ver, int i)
{
	int		j;
	int		ok;

	ok = 0;
	while ((*line)[++i])
	{
		if ((*line)[i] != ' ')
			ok = 1;
	}
	while (!ok && *ver != 2)
	{
		j = i;
		if (!(*line = get_newline(line, ver, '|', ' ')))
			return (0);
		while (*ver != 2 && (*line)[j])
		{
			if ((*line)[j] == '|' && !behind_pipe(*line, j, i, ver))
				return (1);
			if ((*line)[j] != ' ')
				return (1);
			j++;
		}
	}
	return (1);
}

int		back_slash(char **line, int *ver, char *c, int *i)
{
	char	*tmp;
	int		j;
	int		max;

	if (*i == 0 && !(get_newline(line, ver, *c, '\0')))
		return (-1);
	if (*i != 0)
	{
		j = -1;
		if (!(tmp = ft_strdup(*line)))
			return (-1);
		max = ft_strlen(tmp) - 2;
		free(*line);
		if (!(*line = malloc(sizeof(char) * (max + 1))))
			return (-1);
		while (++j < max)
			(*line)[j] = tmp[j];
		(*line)[j] = '\0';
		if (!(get_newline(line, ver, *c, tmp[j])))
			return (-1);
		free(tmp);
	}
	return (1);
}

int		loop_quote(char **line, int *ver, char *c, int *i)
{
	int		comp;

	comp = 0;
	if (enter_quote(*line, *i))
	{
		comp++;
		*c = (*line)[(*i)++];
		quote_bbis((*line), i, *c, &comp);
	}
	else if (enter_slash(*line, *i, '|'))
	{
		if (!(get_newpipe(line, ver, (*i)++)))
			return (-1);
	}
	else if ((*line)[*i] == '\\' && \
	(*line)[*i + 1] == '\0' && !verif_slash(*line, *i))
	{
		if ((back_slash(line, ver, c, i)) == -1)
			return (-1);
	}
	else
		(*i)++;
	return (comp);
}

char	*quote(char **line, int *ver)
{
	int		comp;
	char	c;

	comp = 1;
	while (comp % 2 == 1)
	{
		comp = 0;
		if ((comp = quote_bis(line, ver, &c)) == -1)
			return (NULL);
		if (*ver != 2 && comp % 2 == 1)
		{
			if (!(*line = get_newline(line, ver, c, '\n')))
				return (NULL);
		}
		if (*ver == 2)
			return (NULL);
	}
	return (*line);
}
