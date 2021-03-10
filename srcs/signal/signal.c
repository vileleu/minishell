/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 17:06:48 by vileleu           #+#    #+#             */
/*   Updated: 2021/03/10 15:57:05 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	sigint_signal(int n)
{
	if (n == SIGINT)
	{
		if (g_fork / 1000 == 2 || g_fork / 1000 == 5)
		{
			exit(EXIT_SUCCESS);
		}
		if (g_fork / 1000 == 1 || g_fork / 1000 == 4)
		{
			ft_putchar_fd('\n', 1);
			g_fork = 1130;
		}
		if (g_fork / 1000 == 0)
		{
			put_name("\nminishell", ": ", 1);
			g_fork = 130;
		}
	}
}

void	sigquit_signal(int n)
{
	if (n == SIGQUIT)
	{
		if (g_fork / 1000 == 2)
			exit(EXIT_SUCCESS);
		if (g_fork / 1000 == 1)
		{
			ft_putstr_fd("Quit: ", 1);
			g_fork = 1131;
		}
		if (g_fork / 1000 == 0 || g_fork / 1000 == 4)
			ft_putstr_fd("\b\b  \b\b", 1);
	}
}

int		ret_signal(t_o *o)
{
	if (g_fork - ((g_fork / 1000) * 1000) == 131)
		o->ret = "?=131";
	else if (g_fork - ((g_fork / 1000) * 1000) == 130)
		o->ret = "?=130";
	else
		o->ret = "?=2";
	g_fork = 0;
	return (1);
}
