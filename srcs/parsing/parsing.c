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

char	*verif_syntax(t_o *o, char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == ';' && i == 0)
			return (error_syntx(o, "syntax error near unexpected token", ";"));
		if (line[i] == ';' && line[i + 1] == ';')
			return (error_syntx(o, "syntax error near unexpected token", ";;"));
		i++;
	}
	return ("?=0");
}

int		parsing_work(char **line, t_o *o)
{
	char	**multi;
	char	*ret;
	int		i;

	i = 0;
	if (!(*line = quote(*line)))
		return (0);
	ret = verif_syntax(o, *line);
	if (ft_strcmp(ret, "?=0") != 0)
	{
		o->ret = ret;
		return (1);
	}
	if (!(multi = ft_split_s(*line, ';')))
		return (0);
	while (o->exit && multi[i])
	{
		if (!(work_in(o, multi[i])))
			return (free_all(multi, NULL, 0));
		i++;
	}
	return (1);
}
