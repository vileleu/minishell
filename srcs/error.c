/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vileleu <vileleu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 15:54:39 by vileleu           #+#    #+#             */
/*   Updated: 2020/10/05 16:47:29 by vileleu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*error_leave(char *s, char *line)
{
	if (line != NULL)
		free(line);
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", 2);
	return (NULL);
}

int		error_leave_int(char *s, char *line)
{
	if (line != NULL)
		free(line);
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(s, 2);
	ft_putstr_fd("\n", 2);
	return (0);
}

char	*error_errno(char **cmd)
{
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(cmd[1], 2);
	ft_putstr_fd("\n", 2);
	return (ft_strdup(""));
}

char	*error_arg(char **cmd)
{
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd(": too many arguments\n", 2);
	return (ft_strdup(""));
}

int		free_all(char **cmd, char *output, char *line)
{
	int		i;

	i = 0;
	while (cmd[i])
		free(cmd[i++]);
	free(cmd);
	free(output);
	if (line != NULL)
		free(line);
	return (0);
}