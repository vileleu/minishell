/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vileleu <vileleu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:25:25 by vileleu           #+#    #+#             */
/*   Updated: 2020/10/29 17:23:17 by vileleu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ctoc(char c, int n)
{
	if (c == ';' && n == 1)
		return (";");
	else if (c == ';' && n == 2)
		return (";;");
	else if (c == '|' && n == 1)
		return ("|");
	else
		return ("||");
}

int		empty_synt(char	*line, int	i)
{
	int		ok;

	ok = 1;
	i--;
	while (i >= 0 && line[i] != ';' && line[i] != '|')
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\v' \
		&& line[i] != '\f' && line[i] != '\r' && line[i] != '\n')
			ok = 0;
		i--;
	}
	return (ok);
}

int		verif_synt(t_o *o, char *l, char c, int i)
{
	char	str[] = "syntax error near unexpected token";
	char	m;

	while (l[++i])
	{
		if (l[i] == '\'' || l[i] == '\"')
		{
			m = l[(i)++];
			while (l[i] && l[i] != m)
				(i)++;
			if (l[i] == '\0')
				return (1);
		}
		if (l[i] == c && l[i + 1] == c)
		{
			o->ret = error_syntx(o, str, ctoc(l[i], 2));
			return (0);
		}
		if (l[i] == c && (i == 0 || empty_synt(l, i)))
		{
			o->ret = error_syntx(o, str, ctoc(l[i], 1));
			return (0);
		}
	}
	return (1);
}

int		parsing_pipe(t_o *o, char *multi)
{
	char	**pipe;
	int		i;

	i = 0;
	if (!(pipe = ft_split_s(multi, '|')))
		return (0);
	while (pipe[i])
	{
		while (pipe[i + 1])
		{
			if (!(work_in(o, &(pipe[i]), 1)))
				return (free_all(&pipe, NULL, 0));
			if (!(pipe[i + 1] = ft_strjoin_sp(pipe[i + 1], o->out, ' ')))
				return (free_all(&pipe, &(o->out), 0));
			free(o->out);
			i++;
		}
		if (!(work_in(o, &(pipe[i]), 0)))
			return (free_all(&pipe, NULL, 0));
		i++;
	}
	return (free_all(&pipe, NULL, 1));
}

int		parsing_work(char **line, t_o *o)
{
	char	**multi;
	int		i;

	i = 0;
	if (!(verif_synt(o, *line, ';', -1)) || !(verif_synt(o, *line, '|', -1)))
		return (1);
	if (!(*line = quote(*line)))
		return (0);
	PROMPT = 0;
	if (!(multi = ft_split_s(*line, ';')))
		return (0);
	while (o->exit && multi[i])
	{
		if (!(parsing_pipe(o, multi[i])))
			return (free_all(&multi, NULL, 0));
		i++;
	}
	return (free_all(&multi, NULL, 1));
}
