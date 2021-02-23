/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vileleu <vileleu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 16:30:52 by vileleu           #+#    #+#             */
/*   Updated: 2021/02/23 17:14:11 by vileleu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int		change_line(char **line, char *tmp)
{
	free(*line);
	*line = ft_strdup(tmp);
	free(tmp);
	return (1);
}

int		read_cmd(char *line, int beg, int end)
{
	char	*name;
	int		i;
	int		fd;

	beg++;
	while (is_empty(line[beg]))
		beg++;
	if (!(name = malloc(sizeof(char) * (end - beg + 1))))
		return (0);
	i = 0;
	while (beg < end)
		name[i++] = line[beg++];
	name[i] = '\0';
	fd = open(name, O_RDONLY);
	return (fd);
}

int		take_cmd(t_o *o, char **line, int beg, int end)
{
	char	*tmp;
	int		end_cpy;
	int		i;

	end_cpy = end;
	i = -1;
	if (!(tmp = malloc(sizeof(char) * (ft_strlen(*line) - (end - beg) + 1))))
		return (0);
	while (++i < beg)
		tmp[i] = (*line)[i];
	while ((*line)[end])
		tmp[i++] = (*line)[end++];
	tmp[i] = '\0';
	i = beg + 1;
	while ((*line)[++i])
	{
		if ((*line)[i] == '<')
			return (change_line(line, tmp));
	}
	if (!(o->red_in = read_cmd(*line, beg, end_cpy)))
		return (0);
	change_line(line, tmp);
	dup2(o->red_in, 0);
	return (1);
}

int		redi_bis(t_o *o, char **line, int i, int beg)
{
	char	m;
	int		end;

	end = 0;
	if ((*line)[i] == '\"' || (*line)[i] == '\'')
	{
		m = (*line)[i++];
		while ((*line)[i] != m)
			i++;
		end = i;
	}
	else
	{
		while ((*line)[i] && !is_empty((*line)[i]) \
		&& (*line)[i] != '>' && (*line)[i] != '<')
			i++;
		end = i;
	}
	if ((*line)[beg] == '>' && !(where_redi(o, line, beg, end)))
		return (0);
	if ((*line)[beg] == '<' && !(take_cmd(o, line, beg, end)))
		return (0);
	return (1);
}

int		redirections(t_o *o, char **line)
{
	int		i;
	int		beg;

	i = -1;
	while ((*line)[++i])
	{
		if ((*line)[i] == '\"' || (*line)[i] == '\'')
			ignore(*line, &i);
		if ((*line)[i] == '>' || (*line)[i] == '<')
		{
			beg = i++;
			if ((*line)[i] == '>')
				i++;
			while (is_empty((*line)[i]))
				i++;
			if (!(redi_bis(o, line, i, beg)))
				return (0);
			i = -1;
		}
	}
	return (1);
}
