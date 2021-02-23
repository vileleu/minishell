/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vileleu <vileleu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 18:25:25 by vileleu           #+#    #+#             */
/*   Updated: 2021/02/20 14:11:02 by vileleu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int		behind_pipe(char *line, int j, int stop, int *ver)
{
	int		ok;

	ok = 0;
	j--;
	while (j > stop)
	{
		if (line[j] != ' ')
			ok = 1;
		j--;
	}
	if (!ok)
	{
		*ver = 2;
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	}
	return (ok);
}

int		free_pipe(t_pipe *tuy)
{
	t_pipe	*tmp;

	while (tuy)
	{
		tmp = tuy;
		tuy = (tuy)->next;
		free(tmp);
	}
	return (0);
}

int		init_pipe(char **pip, t_pipe **tuy)
{
	t_pipe	*tmp;
	int		i;

	i = 1;
	if (pip[i])
	{
		if (!(*tuy = malloc(sizeof(t_pipe))))
			return (0);
		(*tuy)->next = NULL;
		tmp = *tuy;
		i++;
	}
	while (pip[i])
	{
		if (!(tmp->next = malloc(sizeof(t_pipe))))
			return (free_pipe(*tuy));
		tmp = tmp->next;
		tmp->next = NULL;
		i++;
	}
	return (i);
}

int		loop_pipe(t_o *o, char **pip, t_pipe **tuy, int i)
{
	if (i != 0 && pip[(i) + 1])
	{
		pipe((*tuy)->next->fd);
		dup2(((*tuy)->next->fd)[1], 1);
	}
	else if (i != 0 && !pip[(i) + 1])
		dup2(o->savout, 1);
	if (!(work_in(o, &(pip[i]))))
		return (0);
	if (i != 0 && pip[(i) + 1])
	{
		close((*tuy)->fd[0]);
		close(((*tuy)->next->fd)[1]);
		dup2(((*tuy)->next->fd)[0], 0);
		*tuy = (*tuy)->next;
	}
	else if (i == 0)
		close(((*tuy)->fd)[1]);
	return (1);
}

int		begin_pipe(t_o *o, char **pip, t_pipe **tuy, int n)
{
	t_pipe	*save;
	int		i;

	i = 0;
	save = *tuy;
	pipe((*tuy)->fd);
	dup2(((*tuy)->fd)[0], 0);
	dup2(((*tuy)->fd)[1], 1);
	while (i < n)
	{
		if (!(loop_pipe(o, pip, tuy, i)))
			return (0);
		close_all(o, 0);
		i++;
	}
	close(((*tuy)->fd)[0]);
	dup2(o->savin, 0);
	free_pipe(save);
	return (1);
}
