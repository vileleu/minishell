/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 16:22:13 by vileleu           #+#    #+#             */
/*   Updated: 2021/03/10 15:54:28 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int		where_path(char **path, char *s)
{
	int		i;

	i = 0;
	while (s[i] && s[i] != ':')
		i++;
	if (i == 0)
		return (0);
	if (!(*path = malloc(sizeof(char) * (i + 1))))
		return (-1);
	i = 0;
	while (s[i] && s[i] != ':')
	{
		(*path)[i] = s[i];
		i++;
	}
	(*path)[i] = '\0';
	return (i);
}

int		execute(char **path, t_o *o, char **cmd)
{
	char	**envp;
	pid_t	pid;
	int		exit_pid;

	exit_pid = 0;
	if (!(envp = new_envp(o)))
		return (0);
	o->out = ft_strdup("");
	g_fork = 1000;
	if (!ft_strcmp(cmd[0], "man") || !ft_strcmp(cmd[0], "minishell"))
		g_fork = 3000;
	pid = fork();
	if (pid == -1)
		return (free_all(&envp, NULL, 0));
	else if (pid > 0)
		waitpid(pid, &exit_pid, 0);
	else if (pid == 0)
	{
		g_fork = 2000;
		if (execve(*path, cmd, envp) == -1 && free_all(&envp, NULL, -1))
			error_exec(o, *path);
	}
	return_child(o, exit_pid);
	return (free_all(&envp, NULL, 2));
}

int		find_exe(char **path, char **cmd, t_o *o)
{
	DIR				*dir;
	struct dirent	*sd;
	int				fd;

	if (!(dir = opendir(*path)))
		return (1);
	while ((sd = readdir(dir)) != NULL)
	{
		if (ft_strcmp(sd->d_name, cmd[0]) == 0)
		{
			o->fd = 0;
			if ((*path)[ft_strlen(*path) - 1] != '/' && \
			!(*path = ft_strjoin(*path, "/")))
				return (closedir(dir));
			if (!(*path = ft_strjoin(*path, cmd[0])))
				return (closedir(dir));
			if ((fd = open(*path, O_DIRECTORY)) > 0)
				return (close_dir(dir, fd, -2));
			close_dir(dir, fd, 1);
			return (execute(path, o, cmd));
		}
	}
	closedir(dir);
	return (1);
}

int		find_path(char *s, t_o *o)
{
	char	*path;
	int		ret;
	int		i;
	int		end;

	i = 0;
	end = 1;
	while ((ret = where_path(&path, s + i)) > 0)
	{
		if (!(end = find_exe(&path, o->cmd, o)))
			return (big_free(&path, NULL));
		free(path);
		if (s[i + ret] == '\0' || end == 2)
			break ;
		i += ret + 1;
	}
	return (end);
}

int		cmd_path(t_o *o)
{
	t_list	*tmp;
	int		ret;

	tmp = o->ev;
	ret = 1;
	while (tmp)
	{
		if (ft_strcmp_eg(tmp->content, "PATH") == 0)
		{
			if (!(ret = find_path(tmp->content + 5, o)))
				return (0);
			break ;
		}
		tmp = tmp->next;
	}
	return (ret);
}
