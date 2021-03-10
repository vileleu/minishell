/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 19:47:04 by vileleu           #+#    #+#             */
/*   Updated: 2021/03/10 17:42:23 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int		for_digit(t_o *o, char **line, int *i, int v)
{
	char	*fake;

	if (!(fake = create_fake(*line, i, 1, v)))
		return (0);
	if (!(replace(line, i, fake, o)))
		return (free_all(NULL, &fake, 0));
	return (free_all(NULL, &fake, 1));
}

int		for_ev_strdup(char **line, int *i, int v, t_o *o)
{
	if (ft_isdigit((*line)[*i + 1]))
	{
		if (!(for_digit(o, line, i, v)))
			return (0);
	}
	else
	{
		if (!(not_ev(line, i, v, o)))
			return (0);
	}
	return (1);
}
