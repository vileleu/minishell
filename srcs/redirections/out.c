/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   out.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vileleu <vileleu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 16:22:13 by vileleu           #+#    #+#             */
/*   Updated: 2021/02/20 17:12:01 by vileleu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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

int		create_file(char *line, int beg, int end)
{
	char	*name;
	int		i;
	int		fd;
	int		doub;

	doub = 0;
	beg++;
	if (line[beg] == '>' && beg++)
		doub = 1;
	while (is_empty(line[beg]))
		beg++;
	if (!(name = malloc(sizeof(char) * (end - beg + 1))))
		return (0);
	i = 0;
	while (beg < end)
		name[i++] = line[beg++];
	name[i] = '\0';
	if (doub)
		fd = open(name, O_CREAT | O_WRONLY | O_APPEND, S_IRUSR \
		| S_IWUSR | S_IRGRP | S_IROTH);
	else
		fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, S_IRUSR \
		| S_IWUSR | S_IRGRP | S_IROTH);
	free(name);
	return (fd);
}

int		where_redi(t_o *o, char **line, int beg, int end)
{
	char	*tmp;
	int		i;

	i = -1;
	if (!(o->red_out = create_file(*line, beg, end)))
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
		if ((*line)[i] == '>')
			return (not_alone(o));
	}
	dup2(o->red_out, 1);
	return (1);
}
