/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vileleu <vileleu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 15:33:30 by vileleu           #+#    #+#             */
/*   Updated: 2020/10/06 19:01:02 by vileleu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BUF 1

# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <string.h>
# include <errno.h>
# include <dirent.h>
# include "libft.h"

char		*error_leave(char *s, char *line);
int			error_leave_int(char *s, char *line);
char		*error_errno(char **cmd);
char		*error_arg(char **cmd);

char		*cmd_cd(char **cmd);
char		*cmd_echo(char **cmd, int *jmp);
char		*cmd_pwd(char **cmd, int *jmp);
char		*cmd_exit(char **cmd);
char		*unknown(char *s, char **cmd);

int			free_all(char **cmd, char *output, char *line);
void		put_name(char *name, char *sup, int fd);
char		*quote(char *line);

#endif