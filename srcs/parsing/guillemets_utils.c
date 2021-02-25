/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guillemets_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vileleu <vileleu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:35:01 by vileleu           #+#    #+#             */
/*   Updated: 2021/02/25 15:59:16 by vileleu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int		verif_slash(char *line, int i)
{
	int		comp;

	comp = 0;
	while (i >= 0 && line[i] == '\\')
	{
		comp++;
		i--;
	}
	if (comp % 2 == 1)
		return (0);
	else
		return (1);
}

void	quote_bbis(char *line, int *i, char c, int *comp)
{
	while (line[*i])
	{
		if (is_quote(line, *i, c))
		{
			(*comp)++;
			(*i)++;
			break ;
		}
		(*i)++;
	}
}

int		quote_bis(char **line, int *ver, char *c)
{
	int		i;
	int		comp;

	i = 0;
	comp = 0;
	while (*ver != 2 && (*line)[i])
	{
		if ((comp += loop_quote(line, ver, c, &i)) == -1)
			return (-1);
	}
	return (comp);
}
