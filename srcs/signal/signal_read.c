/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_read.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 17:06:48 by vileleu           #+#    #+#             */
/*   Updated: 2021/03/10 15:57:46 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int		get_child_p(char **newline, int fd[2], int *end)
{
	char	buf[2];
	int		rd;
	int		ok;

	ok = 0;
	close(fd[1]);
	wait(NULL);
	*newline = ft_strdup("");
	while ((rd = read(fd[0], &buf, 1)) > 0)
	{
		buf[rd] = '\0';
		if (!ok++)
			*end = buf[0] - '0';
		else
		{
			if (!(*newline = ft_strjoin(*newline, buf)))
				return (0);
		}
	}
	if (rd == -1)
		return (0);
	close(fd[0]);
	return (1);
}

void	get_child_c(char *newline, int fd[2], int end)
{
	char buf[2];

	close(fd[0]);
	if ((end = get_next_line(0, &newline)) < 0)
		exit(EXIT_FAILURE);
	buf[0] = end + '0';
	buf[1] = '\0';
	ft_putstr_fd(buf, fd[1]);
	ft_putstr_fd(newline, fd[1]);
	close(fd[1]);
	free(newline);
	exit(EXIT_SUCCESS);
}

char	*get_child(int *end)
{
	char	*newline;
	pid_t	pid;
	int		fd[2];

	newline = NULL;
	pipe(fd);
	g_fork = 4000;
	pid = fork();
	if (pid == -1)
		return (NULL);
	else if (pid == 0)
	{
		g_fork = 5000;
		get_child_c(newline, fd, *end);
	}
	else if (pid > 0)
	{
		if (!(get_child_p(&newline, fd, end)))
			return (NULL);
	}
	return (newline);
}

char	*little_itoa(int n)
{
	if (n == 1)
		return ("?=1");
	else if (n == 2)
		return ("?=2");
	else if (n == 3)
		return ("?=3");
	else
		return ("?=0");
}

void	return_child(t_o *o, int exit_pid)
{
	if (WIFEXITED(exit_pid))
	{
		exit_pid = WEXITSTATUS(exit_pid);
		o->ret = little_itoa(exit_pid);
	}
	else if (WIFSIGNALED(exit_pid))
	{
		if (g_fork - ((g_fork / 1000) * 1000) == 131)
		{
			o->ret = "?=131";
			printf("%d\n", exit_pid);
		}
		else if (g_fork - ((g_fork / 1000) * 1000) == 130)
			o->ret = "?=130";
	}
	g_fork = 0;
}
