/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_others.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 16:22:13 by vileleu           #+#    #+#             */
/*   Updated: 2021/03/10 16:54:27 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int		verif_others(char *line, int beg, char c)
{
	int		i;
	char	m;

	i = beg;
	while (line[++i])
	{
		if (enter_quote(line, i))
		{
			m = line[i++];
			while (!is_quote(line, i, m))
				i++;
		}
		if (enter_slash(line, i, c))
			return (1);
	}
	return (0);
}
