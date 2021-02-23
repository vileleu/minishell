/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guillemets.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vileleu <vileleu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 15:11:21 by vileleu           #+#    #+#             */
/*   Updated: 2021/02/23 14:24:44 by vileleu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*get_newline(char **line, int *ver, char c, char join)
{
	char	*newline;
	int		end;

	NL = 1;
	put_name("> ", "", 2);
	if (!(newline = get_child(&end)))
		return (NULL);
	if (!end || !NL)
	{
		*ver = 2;
		free(newline);
		return (error_eof(line, c, join));
	}
	NL = 0;
	if (!(*line = ft_strjoin_sp(*line, newline, join)))
		return (NULL);
	free(newline);
	return (*line);
}

void	quote_bbis(char *line, int *i, char c, int *comp)
{
	while (line[*i])
	{
		if (line[*i] == c)
		{
			(*comp)++;
			(*i)++;
			break ;
		}
		(*i)++;
	}
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

int		quote_bis(char **line, int *ver, char *c)
{
	int		i;
	int		comp;

	i = 0;
	comp = 0;
	while (*ver != 2 && (*line)[i])
	{
		if ((*line)[i] == '"' || (*line)[i] == '\'')
		{
			comp++;
			*c = (*line)[i++];
			quote_bbis((*line), &i, *c, &comp);
		}
		else if ((*line)[i] == '|')
		{
			if (!(get_newpipe(line, ver, i)))
				return (-1);
			i++;
		}
		else
			i++;
	}
	return (comp);
}

char	*quote(char **line, int *ver)
{
	int		comp;
	char	c;

	comp = 1;
	while (comp == 1)
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
