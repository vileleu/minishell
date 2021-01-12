/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 19:47:04 by vileleu           #+#    #+#             */
/*   Updated: 2021/01/12 13:19:54 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*create_fake(char *line, int *i, int j, int v)
{
	char	*tmp;
	int		k;

	k = 0;
	if (v == 2)
		j = 0;
	if (!(tmp = malloc(sizeof(char) * (j + 2))))
		return (NULL);
	while (k < j)
	{
		tmp[k] = line[*i + 1 + k];
		k++;
	}
	tmp[k++] = '=';
	tmp[k] = '\0';
	return (tmp);
}

int		replace(char **line, int *i, char *s, t_o *o)
{
	char	*beg;
	char	*end;
	char	*tmp;
	int		len;
	int		j;

	len = ft_strlen(s) - ft_strlen_ev(s);
	if (!(beg = malloc(sizeof(char) * (*i + 1))))
		return (0);
	j = -1;
	while (++j < *i)
		beg[j] = (*line)[j];
	beg[j] = '\0';
	if (!(end = ft_strdup((*line) + *i + len)))
		return (big_free(&beg, NULL));
	if (!(tmp = ft_strjoin(beg, s + len)))
		return (big_free(&beg, &end));
	free(*line);
	if (!(*line = ft_strjoin(tmp, end)))
		return (big_free(&end, NULL));
	free(end);
	o->len = ft_strlen_ev(s);
	return (1);
}

int		not_ev_bis(char **l, int *i, int v, t_o *o)
{
	char	*tmp;

	if (--(o->i) > 0)
	{
		if (!(tmp = create_fake(*l, i, o->i, v)))
			return (0);
		if (!(replace(l, i, tmp, o)))
			return (big_free(&tmp, NULL));
		free(tmp);
		return (1);
	}
	if (v == 0 && ((*l)[(*i) + 1] < 'a' || (*l)[(*i) + 1] > 'z') && \
	((*l)[(*i) + 1] < 'A' || (*l)[(*i) + 1] > 'Z') && (*l)[(*i) + 1] != '_')
		o->len = 1;
	return (1);
}

int		not_ev(char **l, int *i, int v, t_o *o)
{
	int		j;
	int		tmp;

	j = 0;
	while ((*l)[++j + *i])
	{
		if (((*l)[j + *i] == '"' || (*l)[j + *i] == '\'') && v && j == 1)
		{
			v++;
			j++;
			break ;
		}
		if (((*l)[j + *i] < 'a' || (*l)[j + *i] > 'z') && ((*l)[j + *i] < 'A' || \
		(*l)[j + *i] > 'Z') && (*l)[j + *i] != '_' && j == 1)
			break ;
		if (((*l)[j + *i] < 'a' || (*l)[j + *i] > 'z') && ((*l)[j + *i] < 'A' || (*l)[j + \
		*i] > 'Z') && ((*l)[j + *i] < '0' || (*l)[j + *i] > '9') && (*l)[j + *i] != '_')
			break ;
	}
	tmp = o->i;
	o->i = j;
	if (!(not_ev_bis(l, i, v, o)))
		return (0);
	o->i = tmp;
	return (1);
}

int		ev_strdup(char **line, int *i, t_o *o, int v)
{
	t_list	*tmp;

	tmp = o->ev;
	while (tmp)
	{
		if (ft_strcmp_ev(tmp->content, *line + *i + 1) == 0)
		{
			if (!(replace(line, i, tmp->content, o)))
				return (0);
			return (1);
		}
		tmp = tmp->next;
	}
	if (ft_strncmp(o->ret, *line + *i + 1, 1) == 0)
	{
		if (!(replace(line, i, o->ret, o)))
			return (0);
		return (1);
	}
	else
	{
		if (!(not_ev(line, i, v, o)))
			return (0);
	}
	return (1);
}
