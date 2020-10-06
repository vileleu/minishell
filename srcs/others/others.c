/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vileleu <vileleu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 15:11:21 by vileleu           #+#    #+#             */
/*   Updated: 2020/10/06 19:02:40 by vileleu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cmd_exit(char **cmd)
{
	if (cmd[1] != NULL)
		return (error_arg(cmd));
	return (0);
}

void	put_name(char *s, char *sup, int fd)
{
	ft_putstr_fd("\033[0;35m", fd);
	ft_putstr_fd(s, fd);
	ft_putstr_fd(sup, fd);
	ft_putstr_fd("\033[0m", fd);
}

char	*quote_bis(char *line, char c, int *comp)
{
	char	*newline;
	int		i;

	if (!(newline = ft_strdup(line)))
		return (error_leave("malloc failed", line));
	free(line);
	put_name("> ", "", 2);
	if ((get_next_line(0, &line)) < 0)
		return (error_leave("malloc failed", line));
	i = 0;
	while (line[i])
	{
		if (line[i] == c)
			(*comp)++;
		i++;
	}
	newline = ft_strjoin_sp(newline, line, '\n');
	free(line);
	return (newline);
}

char	*quote(char *line)
{
	int		i;
	int		comp;
	char	c;

	i = 0;
	comp = 0;
	while (line[i])
	{
		if ((line[i] == '"' || line[i] == '\'') && comp == 0)
		{
			comp++;
			c = line[i];
		}
		else if (line[i] == c)
			comp++;
		i++;
	}
	if (comp % 2 == 0)
		return (line);
	while (comp % 2 == 1)
		line = quote_bis(line, c, &comp);
	return (line);
}