/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:25:25 by vileleu           #+#    #+#             */
/*   Updated: 2021/03/10 15:55:29 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*ctoc(char c, int n)
{
	if (c == ';' && n == 1)
		return (";");
	else if (c == ';' && n == 2)
		return (";");
	else if (c == '|' && n == 1)
		return ("|");
	else if (c == '|' && n == 2)
		return ("|");
	else
		return ("newline");
}

int		empty_synt(char *line, int i)
{
	int		ok;

	ok = 1;
	i--;
	while (i >= 0 && line[i] != ';' && line[i] != '|'
		&& line[i] != '>' && line[i] != '<')
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\v' \
		&& line[i] != '\f' && line[i] != '\r' && line[i] != '\n')
			ok = 0;
		i--;
	}
	return (ok);
}

int		syntax_bef(t_o *o, char *line, int i, int *r)
{
	if ((line[i] == '|' && line[i + 1] == '|') || (line[i] == ';'
		&& line[i + 1] == ';'))
	{
		o->ret = error_syntx(o, "syntax error near unexpected token",
			ctoc(line[i], 2));
		*r = 0;
		return (0);
	}
	if ((line[i] == '|' || line[i] == ';')
		&& (i == 0 || empty_synt(line, i)))
	{
		o->ret = error_syntx(o, "syntax error near unexpected token",
			ctoc(line[i], 1));
		*r = 0;
		return (0);
	}
	return (1);
}

int		syntax_aft(t_o *o, char *line, int i, int *r)
{
	*r = 0;
	if (line[i] == '>')
		i++;
	while (line[i] && !enter_slash(line, i, '>') && !enter_slash(line, i, '<'))
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\v' \
		&& line[i] != '\f' && line[i] != '\r' && line[i] != '\n' \
		&& line[i] != '>' && line[i] != '<')
			*r = 1;
		i++;
	}
	if (!(*r) && enter_slash(line, i, '>') && enter_slash(line, i + 1, '>'))
		o->ret = error_syntx(o, "syntax error near unexpected token", ">>");
	else if (!(*r) && enter_slash(line, i, '>'))
		o->ret = error_syntx(o, "syntax error near unexpected token", ">");
	else if (!(*r) && enter_slash(line, i, '<'))
		o->ret = error_syntx(o, "syntax error near unexpected token", "<");
	else if (!(*r))
		o->ret = error_syntx(o, "syntax error near unexpected token",
			"newline");
	return (1);
}

int		parsing_char(t_o *o, char *line)
{
	char	m;
	int		i;
	int		r;

	g_fork = 0;
	i = 0;
	r = 1;
	while (line[i])
	{
		if (enter_quote(line, i))
		{
			m = line[(i)++];
			while (line[i] && line[i] != m)
				(i)++;
		}
		else if (enter_slash(line, i, '>') || enter_slash(line, i, '<'))
			syntax_aft(o, line, ++i, &r);
		else if (enter_slash(line, i, ';') || enter_slash(line, i, '|'))
			syntax_bef(o, line, i++, &r);
		else
			i++;
		if (!r)
			return (r);
	}
	return (r);
}
