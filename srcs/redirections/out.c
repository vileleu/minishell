/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vileleu <vileleu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 16:22:13 by vileleu           #+#    #+#             */
/*   Updated: 2021/02/25 15:52:07 by vileleu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	ignore(char *line, int *i)
{
	char	m;

	m = line[(*i)++];
	while (!is_quote(line, *i, m))
		(*i)++;
}

int		not_alone(t_o *o)
{
	close(o->red_out);
	o->red_out = 0;
	return (1);
}

int		is_empty(char c)
{
	if (c == ' ' || c == '\t' || c == '\v' \
	|| c == '\f' || c == '\r')
		return (1);
	return (0);
}

int		create_file(t_o *o, char *line, int beg, int end)
{
	char	**new;
	char	*name;
	int		fd;
	int		doub;

	if (!(name = create_file_bis(line, &beg, &end, &doub)))
		return (0);
	if (!(new = ft_split_m(&name, ' ', o)))
		return (free_all(NULL, &name, 0));
	if (doub)
	{
		if ((fd = open(new[0], O_CREAT | O_WRONLY | O_APPEND, S_IRUSR \
		| S_IWUSR | S_IRGRP | S_IROTH)) == -1)
			return (error_open(o, &new, &name));
	}
	else
	{
		if ((fd = open(new[0], O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR \
		| S_IWUSR | S_IRGRP | S_IROTH)) == -1)
			return (error_open(o, &new, &name));
	}
	free_all(&new, &name, 1);
	return (fd);
}

int		where_redi(t_o *o, char **line, int beg, int end)
{
	char	*tmp;
	int		i;

	i = -1;
	if (!(o->red_out = create_file(o, *line, beg, end)) || o->red_out == -1)
		return (0);
	if (!(tmp = malloc(sizeof(char) * (ft_strlen(*line) - (end - beg) + 1))))
		return (0);
	while (++i < beg)
		tmp[i] = (*line)[i];
	while ((*line)[end])
		tmp[i++] = (*line)[end++];
	tmp[i] = '\0';
	free(*line);
	*line = ft_strdup(tmp);
	free(tmp);
	i = -1;
	while ((*line)[++i])
	{
		if (enter_slash(*line, i, '>'))
			return (not_alone(o));
	}
	dup2(o->red_out, 1);
	return (1);
}
