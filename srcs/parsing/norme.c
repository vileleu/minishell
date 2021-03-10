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

int		sizeword_bis(t_o *o, char *str, int *j, int *ver)
{
	char	m;
	int		res;

	res = 0;
	if (enter_quote(str, *j) && (*ver)++)
	{
		m = str[*j];
		while (!is_quote(str, ++(*j), m))
		{
			if (str[*j] == '$' && m == '"')
				res += size_ev(str + *j, o, 1);
			if (str[*j] == '\\' && m == '\"' && str[*j + 1] == '$')
			{
				(*j)++;
				res--;
			}
		}
	}
	return (res);
}

int		loop_split_ev_norme(t_o *o, char **s, char *str, int *size)
{
	char	m;

	m = (*s)[(*size)++];
	while (!is_quote(*s, *size, m))
	{
		if ((*s)[*size] == '$' && m == '\"')
		{
			if (!(ev_strdup(s, size, o, 0)))
				return (0);
			while ((o->len)-- > 0)
				str[(o->i)++] = (*s)[(*size)++];
		}
		else if ((*s)[*size] == '\\' && m == '\"' && ((*s)[*size + 1] \
		== '$' || (*s)[*size + 1] == '\"' || (*s)[*size + 1] == '\\'))
		{
			(*size)++;
			str[(o->i)++] = (*s)[(*size)++];
		}
		else
			str[(o->i)++] = (*s)[(*size)++];
	}
	return (1);
}

void	little_norme(t_o *o, char **s, char *str, int *size)
{
	if ((*s)[*size] == '\\')
	{
		(*size)++;
		str[(o->i)++] = (*s)[(*size)++];
	}
}
