/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vileleu <vileleu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 14:41:47 by vileleu           #+#    #+#             */
/*   Updated: 2020/10/06 19:01:47 by vileleu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*commandes(char *s, char **cmd, int *jmp)
{
	if (ft_strncmp(cmd[0], "cd", 3) == 0)
		return (cmd_cd(cmd));
	else if (ft_strncmp(cmd[0], "echo", 5) == 0)
		return (cmd_echo(cmd, jmp));
	else if (ft_strncmp(cmd[0], "pwd", 4) == 0)
		return (cmd_pwd(cmd, jmp));
	else if (ft_strncmp(cmd[0], "exit", 5) == 0)
		return (cmd_exit(cmd));
	else
		return (unknown(s, cmd));
}

int		work_in(char *s, char *line)
{
	char 	**cmd;
	char	*output;
	int		jmp;

	jmp = 0;
	if (!(cmd = ft_split_m(line, ' ')))
		return (error_leave_int("malloc failed", line));
	if (!(output = commandes(s, cmd, &jmp)))
		return (free_all(cmd, output, line));
	ft_putstr(output);
	if (jmp)
		ft_putstr("\n");
	free_all(cmd, output, NULL);
	return (1);
}

char	*loop(char *s)
{
	char	*line;

	line = NULL;
	while (1)
	{
		put_name(s, ": ", 1);
		if ((get_next_line(0, &line)) < 0)
			return (error_leave("malloc failed", line));
		if (!(line = quote(line)))
			return (NULL);
		if (strncmp(line, "", 1) != 0)
		{
			if (!(work_in(s, line)))
				return (NULL);
		}
		free(line);
	}
}

int		main(int ac, char **av)
{
	if (ac != 1)
		return (error_leave_int("too many arguments", NULL));
	loop(av[0] + 2);
	return (0);
}