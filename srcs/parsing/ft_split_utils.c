/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vileleu <vileleu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 16:58:11 by vileleu           #+#    #+#             */
/*   Updated: 2021/02/23 15:37:47 by vileleu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	delete_ev(t_o *o, char *str, int *i, int *nb)
{
	t_list	*tmp;

	if ((str[*i] == '$' && *i == 0) || (str[*i] == '$' && *i > 0 && is_empty(str[*i - 1])))
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
	if ((str[i] == '$' && i == 0) || (str[i] == '$' && i > 0 && is_empty(str[i - 1])))
	{
		tmp = o->ev;
		while (tmp)
		{
			if (!ft_strcmp_ev(tmp->content, str + i + 1))
				return ;
			tmp = tmp->next;
		}
		while (ft_isalnum(str[i]) && str[i])
			i++;
		if (is_empty(str[i]))
			*size = i;
	}
}