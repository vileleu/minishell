/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vileleu <vileleu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:25:25 by vileleu           #+#    #+#             */
/*   Updated: 2021/02/25 16:49:25 by vileleu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	close_all(t_o *o, int n)
{
	if (n)
	{
		close(o->savin);
		close(o->savout);
	}
	if (o->red_out)
	{
		close(o->red_out);
		o->red_out = 0;
	}
	if (o->red_in)
	{
		close(o->red_in);
		o->red_in = 0;
	}
}

int		parsing_pipe(t_o *o, char *multi)
{
	char	**pip;
	int		n;
	t_pipe	*tuy;

	tuy = NULL;
	if (!(pip = ft_split_s(multi, '|')))
		return (0);
	if (!(n = init_pipe(pip, &tuy)))
		return (free_all(&pip, NULL, 0));
	if (n > 1)
	{
		if (!(begin_pipe(o, pip, &tuy, n)))
			return (free_twice(&pip, tuy, 0));
	}
	else if (n == 1)
	{
		if (!(work_in(o, &(pip[0]))))
			return (free_twice(&pip, tuy, 0));
	}
	dup2(o->savin, 0);
	dup2(o->savout, 1);
	close_all(o, 1);
	return (free_all(&pip, NULL, 1));
}

int		parsing_work(char **line, t_o *o)
{
	char	**multi;
	int		i;
	int		ver;

	i = 0;
	ver = 1;
	if (!(parsing_char(o, *line)))
		return (1);
	if (!(quote(line, &ver)) && ver == 1)
		return (0);
	else if (ver == 2 && ft_strcmp(*line, "exit"))
		return (ret_signal(o));
	if (!(parsing_char(o, *line)))
		return (1);
	if (!(multi = ft_split_s(*line, ';')))
		return (0);
	while (o->exit && multi[i])
	{
		o->savin = dup(0);
		o->savout = dup(1);
		if (!(parsing_pipe(o, multi[i])))
			return (free_all(&multi, NULL, 0));
		i++;
	}
	return (free_all(&multi, NULL, 1));
}
