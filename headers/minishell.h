/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vileleu <vileleu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 15:33:30 by vileleu           #+#    #+#             */
/*   Updated: 2020/10/01 18:37:54 by vileleu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BUF 2048

# include <stdio.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../srcs/libft/libft.h"

int			ft_error(char *s);

#endif