/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vileleu <vileleu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 19:42:42 by vileleu           #+#    #+#             */
/*   Updated: 2021/02/25 17:06:55 by vileleu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int		guill(char *str)
{
	int		i;
	int		c;

	i = 0;
	c = 0;
	while (str[i])
	{
		if (str[i++] == '"')
			c++;
	}
	return (c);
}

char	*export_str(char *str, char *beg, int lenbeg, int egual)
{
	int		i;
	int		j;
	char	*new;

	lenbeg = lenbeg + guill(str);
	if (!(new = malloc(sizeof(char) * (ft_strlen(str) + lenbeg + 3))))
		return (NULL);
	i = -1;
	while (beg[++i])
		new[i] = beg[i];
	new[i++] = ' ';
	j = 0;
	while (str[j])
	{
		if (str[j] == '"')
			new[i++ + j] = '\\';
		new[i + j] = str[j];
		if (str[j] == '=' && egual++ == 1)
			new[i++ + j + 1] = '"';
		j++;
	}
	if (egual >= 2)
		new[i++ + j] = '"';
	new[i + j] = '\0';
	return (new);
}

void	ft_swap(char **s1, char **s2)
{
	char *swap;

	swap = *s1;
	*s1 = *s2;
	*s2 = swap;
}

char	**sort(t_o *o, int j, t_list *temp)
{
	char	**tmp;

	if (!(tmp = malloc(sizeof(char*) * (ft_lstsize(o->ev) + 1))))
		return (NULL);
	temp = o->ev;
	if (temp == NULL)
		o->fd = 0;
	while (temp)
	{
		if (!(tmp[j++] = export_str(temp->content, "declare -x", \
		ft_strlen("declare -x") + 1, 1)))
			return (NULL);
		temp = temp->next;
	}
	tmp[j] = NULL;
	j = -1;
	while (++j < ft_lstsize(o->ev) - 1)
	{
		if (ft_strcmp(tmp[j], tmp[j + 1]) > 0)
		{
			ft_swap(&tmp[j], &tmp[j + 1]);
			j = -1;
		}
	}
	return (tmp);
}

char	*print_ev(t_o *o)
{
	char	**tmp;
	int		i;

	if (!(tmp = sort(o, 0, NULL)))
		return (NULL);
	o->out = ft_strdup("");
	i = 0;
	while (tmp[i])
	{
		if (i == 0)
		{
			if (!(o->out = ft_strjoin(o->out, tmp[i])))
				return (NULL);
		}
		else
		{
			if (!(o->out = ft_strjoin_sp(o->out, tmp[i], '\n')))
				return (NULL);
		}
		free(tmp[i]);
		i++;
	}
	free(tmp);
	return ("?=0");
}
