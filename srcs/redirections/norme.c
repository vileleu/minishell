/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vileleu <vileleu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 16:22:13 by vileleu           #+#    #+#             */
/*   Updated: 2021/02/25 15:52:07 by vileleu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int		inc(char *line, int *beg)
{
	int	doub;

	doub = 0;
	(*beg)++;
	if (line[*beg] == '>' && (*beg)++)
		doub = 1;
	else if (line[*beg] == '\\')
	{
		(*beg)++;
		return (doub);
	}
	while (is_empty(line[*beg]))
		(*beg)++;
	return (doub);
}

char	*create_file_bis(char *line, int *beg, int *end, int *doub)
{
	char	*name;
	int		i;

	*doub = inc(line, beg);
	if (!(name = malloc(sizeof(char) * (*end - *beg + 1))))
		return (NULL);
	i = 0;
	while (*beg < *end)
		name[i++] = line[(*beg)++];
	name[i] = '\0';
	return (name);
}

int		reset(t_o *o)
{
	o->red_in = 0;
	o->red_out = 0;
	return (-1);
}

int		error_open(t_o *o, char ***new, char **name)
{
	ft_putstr_fd(o->name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd((*new)[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	o->ret = "?=1";
	return (free_all(new, name, -1));
}