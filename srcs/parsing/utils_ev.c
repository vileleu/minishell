/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ev.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vileleu <vileleu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 19:40:27 by vileleu           #+#    #+#             */
/*   Updated: 2020/10/29 17:26:57 by vileleu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Deux fonctions pour calculer la taille des EV a ecrire
*/

int		in_out(char *s, t_o *o, int i)
{
	t_list	*tmp;

	if (i == 1)
		return (1);
	tmp = o->ev;
	while (tmp)
	{
		if (ft_strcmp_ev(tmp->content, s + 1) == 0)
			return (ft_strlen_ev(tmp->content));
		tmp = tmp->next;
	}
	if (ft_strcmp_ev(o->ret, s + 1) == 0)
		return (ft_strlen_ev(o->ret));
	return (0);
}

int		solo(int v)
{
	if (v)
		return (0);
	else
		return (-1);
}

int		size_ev(char *s, t_o *o, int v)
{
	int		len;
	int		i;

	i = 1;
	while (s[i])
	{
		if (s[i] == '?' && i == 1)
			return (ft_strlen(o->ret) - 4);
		if ((s[i] == '"' || s[i] == '\'') && i == 1)
			return (solo(v));
		if ((s[i] < 'a' || s[i] > 'z') && (s[i] < 'A' || s[i] > 'Z') && \
		s[i] != '_' && i == 1)
			break ;
		if ((s[i] < 'a' || s[i] > 'z') && (s[i] < 'A' || s[i] > 'Z') && \
		(s[i] < '0' || s[i] > '9') && s[i] != '_')
			break ;
		i++;
	}
	len = in_out(s, o, i);
	return (len - i);
}

/*
** suite de la fonction ft_split_m.c
*/

int		loop_split_ev_bis(char **s, char *str, int *size, t_o *o)
{
	if ((*s)[*size] == '$')
	{
		if (!(ev_strdup(s, size, o, 1)))
			return (0);
		while ((o->len)-- > 0)
			str[(o->i)++] = (*s)[(*size)++];
	}
	return (1);
}
