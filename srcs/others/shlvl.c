/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 17:06:48 by vileleu           #+#    #+#             */
/*   Updated: 2021/03/10 16:07:37 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int		there_is_slash(t_o *o)
{
	int		i;

	i = 0;
	while (o->cmd[0][i])
	{
		if (o->cmd[0][i] == '/')
			return (1);
		i++;
	}
	return (0);
}

int		close_dir(DIR *dir, int fd, int n)
{
	closedir(dir);
	close(fd);
	return (n);
}

char	*create_shlvl(char *sh, int i)
{
	char	*final;
	char	*beg;
	char	*end;
	int		nb;

	nb = ft_atoi(sh + i);
	if (!(end = ft_itoa(nb + 1)))
		return (NULL);
	if (!(beg = ft_strdup("SHLVL=")))
		return (NULL);
	if (!(final = ft_strjoin(beg, end)))
		return (NULL);
	free(end);
	return (final);
}

char	*shlvl(char *sh)
{
	char	*tmp;
	int		i;

	i = 0;
	while (sh[i] != '=')
		i++;
	i++;
	if (!full_digit(sh + i))
	{
		if (!(tmp = ft_strdup("SHLVL=1")))
			return (NULL);
	}
	else
	{
		if (!(tmp = create_shlvl(sh, i)))
			return (NULL);
	}
	return (tmp);
}

char	*which_inc(char *tmp)
{
	char	*doub;

	if (!ft_strcmp_eg(tmp, "SHLVL"))
	{
		if (!(doub = shlvl(tmp)))
			return (NULL);
	}
	else
	{
		if (!(doub = ft_strdup(tmp)))
			return (NULL);
	}
	return (doub);
}
