/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:25:25 by vileleu           #+#    #+#             */
/*   Updated: 2021/01/12 13:19:48 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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
	else if (ver == 2)
		return (ret_signal(o));
	if (!(parsing_char(o, *line)))
		return (1); 
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
