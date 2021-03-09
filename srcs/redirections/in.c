/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vileleu <vileleu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 16:30:52 by vileleu           #+#    #+#             */
/*   Updated: 2021/03/09 17:17:28 by vileleu          ###   ########.fr       */
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

int		read_cmd(t_o *o, char *line, int beg, int end)
{
	char	**new;
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
	if (!(new = ft_split_m(&name, ' ', o)))
		return (free_all(NULL, &name, 0));
	if ((fd = open(new[0], O_RDONLY)) == -1)
		return (error_open(o, &new, &name));
	free_all(&new, &name, 1);
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
	i = beg;
	while ((*line)[++i])
	{
		if (enter_slash(*line, i, '<'))
			return (change_line(line, tmp));
	}
	if (!(o->red_in = read_cmd(o, *line, beg, end_cpy)) || o->red_in == -1)
		return (free_all(NULL, &tmp, 0));
	change_line(line, tmp);
	dup2(o->red_in, 0);
	return (1);
}

int		redi_bis(t_o *o, char **line, int i, int beg)
{
	char	m;
	int		end;

	end = 0;
	if (enter_quote(*line, i))
	{
		m = (*line)[i++];
		while (!is_quote(*line, i, m))
			i++;
		i++;
	}
	else
	{
		while ((*line)[i] && !is_empty((*line)[i]) \
		&& !enter_slash(*line, i, '>') && !enter_slash(*line, i, '<'))
		{
			if ((*line)[i] == '\\')
				i++;
			i++;
		}
	}
	end = i;
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
	int		ret;

	i = -1;
	while ((*line)[++i])
	{
		if (enter_quote(*line, i))
			ignore(*line, &i);
		if (enter_slash(*line, i, '>') || enter_slash(*line, i, '<'))
		{
			beg = i++;
			if ((*line)[i] == '>')
				i++;
			while (is_empty((*line)[i]))
				i++;
			if (!(ret = redi_bis(o, line, i, beg)) && (o->red_in == -1 || o->red_out == -1))
				return (reset(o));
			else if (!ret)
				return (0);
			i = -1;
		}
	}
	return (1);
}
