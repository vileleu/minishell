/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vileleu <vileleu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 16:58:11 by vileleu           #+#    #+#             */
/*   Updated: 2021/02/21 17:26:16 by vileleu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	delete_ev(t_o *o, char *str, int *i, int *nb)
{
	t_list	*tmp;

	if (str[*i] == '$')
	{
		tmp = o->ev;
		while (tmp)
		{
			if (!ft_strcmp_eg(str + *i + 1, tmp->content))
				(*nb)--;
			tmp = tmp->next;
		}
	}
	(*i)++;
}

void	delete_after(t_o *o, char *str, int *i)
{
	
}