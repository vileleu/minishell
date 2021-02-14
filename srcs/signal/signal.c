/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 17:06:48 by vileleu           #+#    #+#             */
/*   Updated: 2021/01/12 13:20:12 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	sigint_signal(int n)
{
	if (n == SIGINT)
	{
		if (IN_FORK == 2)
			ft_putchar_fd('\n', 1);
		if (IN_FORK == 2)
			exit(EXIT_SUCCESS);
		if (IN_FORK == 1 && !MAN_FORK)
			ft_putchar_fd('\n', 1);
		if (PROMPT)
			put_name("\nminishell", ": ", 1);
	}
	NL = 0;
	RET_SIG = 130;
}

void	sigquit_signal(int n)
{
	if (n == SIGINT)
	{
		if (IN_FORK == 2)
			ft_putchar_fd('\n', 1);
		if (IN_FORK == 2)
			exit(EXIT_SUCCESS);
		if (IN_FORK == 1 && !MAN_FORK)
			ft_putchar_fd('\n', 1);
		if (PROMPT)
			put_name("\nminishell", ": ", 1);
	}
	NL = 0;
	RET_SIG = 131;
}

int		ret_signal(t_o *o)
{
	if (NL == -1)
	{
		if (RET_SIG == 131)
			o->ret = "?=131";
		else if (RET_SIG == 130)
			o->ret = "?=130";
	}
	else
		o->ret = "?=2";
	RET_SIG = 0;
	return (1);
}
