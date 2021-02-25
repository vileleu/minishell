/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vileleu <vileleu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 16:58:11 by vileleu           #+#    #+#             */
/*   Updated: 2021/02/25 15:54:02 by vileleu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int		enter_quote(char *line, int i)
{
	if ((line[i] == '\"' || line[i] == '\'') && ((i == 0) || (i != 0 && line[i - 1] != '\\')))
		return (1);
	return (0);
}

int		is_quote(char *line ,int i, char m)
{
	if (line[i] == m && m == '\'')
		return (1);
	else if (line[i] == m && ((i == 0) || (i != 0 && line[i - 1] != '\\')))
		return (1);
	return (0);
}

void	delete_ev(t_o *o, char *str, int *i, int *nb)
{
	t_list	*tmp;

	if (((str[*i] == '$' && *i == 0) || (str[*i] == '$' && *i > 0 \
	&& is_empty(str[*i - 1]))) && (ft_isalpha(str[*i + 1]) && str[*i + 1]))
	{
		tmp = o->ev;
		(*i)++;
		while (tmp)
		{
			if (!ft_strcmp_ev(tmp->content, str + *i))
				return ;
			tmp = tmp->next;
		}
		while (ft_isalnum(str[*i]) && str[*i])
			(*i)++;
		if (is_empty(str[*i]) || !str[*i])
			(*nb)--;
	}
	else
		(*i)++;
}

void	delete_after(t_o *o, char *str, int *size)
{
	t_list	*tmp;
	int		i;

	i = *size;
	if (((str[i] == '$' && i == 0) || (str[i] == '$' && i > 0 && \
	is_empty(str[i - 1]))) && (ft_isalpha(str[i + 1]) && str[i + 1]))
	{
		tmp = o->ev;
		while (tmp)
		{
			if (!ft_strcmp_ev(tmp->content, str + i + 1))
				return ;
			tmp = tmp->next;
		}
		i++;
		while (ft_isalnum(str[i]) && str[i])
			i++;
		while (is_empty(str[i]))
			i++;
		*size = i;
	}
}
