/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vileleu <vileleu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 14:36:07 by vileleu           #+#    #+#             */
/*   Updated: 2020/10/05 18:12:03 by vileleu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cmd_cd(char **cmd)
{
	if (cmd[1] == NULL)
		return (ft_strdup(""));
	if (cmd[2] != NULL)
		return (error_arg(cmd));
	if ((chdir(cmd[1])) < 0)
		return (error_errno(cmd));
	return (ft_strdup(""));
}

char	*cmd_pwd(char **cmd, int *jmp)
{
	char	*path;

	if (cmd[1] != NULL)
		return (error_arg(cmd));
	if (!(path = getcwd(NULL, 0)))
		return (error_errno(cmd));
	*jmp = 1;
	return (path);
}

void	jump_echo(char **cmd, int *jmp, int *ii)
{
	int		i;
	int		j;

	i = 0;
	while (cmd[i])
	{
		j = 0;
		while (cmd[i][j])
		{
			if (cmd[i][j] == '\n')
			{
				if (*ii == 2)
				{
					*jmp = 1;
					(*ii)--;
				}
			}
			j++;
		}
		i++;
	}
}

char	*cmd_echo(char **cmd, int *jmp)
{
	int		i;
	char	*output;

	i = 1;
	*jmp = 1;
	if (strncmp(cmd[i], "-n", 3) == 0 && i++)
		*jmp = 0;
	jump_echo(cmd, jmp, &i);
	output = ft_strdup("");
	while (cmd[i])
	{
		if ((i == 1 && *jmp == 1) || (i == 2 && *jmp == 0))
		{
			if (!(output = ft_strjoin(output, cmd[i])))
				return (NULL);
		}
		else
		{
			if (!(output = ft_strjoin_sp(output, cmd[i], ' ')))
				return (NULL);
		}
		i++;
	}
	return (output);
}

char	*unknown(char *s, char **cmd)
{
	put_name(s, ": ", 2);
	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(cmd[0], 2);
	ft_putstr_fd("\n", 2);
	return (ft_strdup(""));
}