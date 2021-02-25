/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vileleu <vileleu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 17:49:51 by vileleu           #+#    #+#             */
/*   Updated: 2021/02/25 16:45:09 by vileleu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int		free_twice(char ***cmd, t_pipe *tuy, int ret)
{
	int		i;

	i = 0;
	if (cmd != NULL)
	{
		while ((*cmd)[i])
			free((*cmd)[i++]);
		free(*cmd);
	}
	if (tuy != NULL)
		free_pipe(tuy);
	return (ret);
}

char	*error_eof(char **line, char c, char join)
{
	if (!NL)
		NL = -1;
	else if (join == '\n')
	{
		ft_putstr_fd("minishell: unexpected EOF while looking for matching `",
			2);
		ft_putchar_fd(c, 2);
		ft_putstr_fd("'\nminishell: syntax error: unexpected end of file\n", 2);
	}
	else if (join == ' ')
	{
		ft_putstr_fd("minishell: syntax error: unexpected end of file\n", 2);
	}
	else
	{
		free(*line);
		*line = ft_strdup("exit");
	}
	return ("");
}

char	*free_char(char **str)
{
	if (*str)
		free(*str);
	return (NULL);
}
