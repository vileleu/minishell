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
		if (PARENT_PID != getpid())
			kill(getpid(), SIGKILL);
		if (PARENT_PID == getpid())
			write(1, "\n", 1);
		if (PARENT_PID == getpid() && PROMPT)
			put_name("minishell", ": ", 1);
	}
}

void	sigquit_signal(int n)
{
	if (n == SIGQUIT)
	{
		if (PARENT_PID != getpid())
			kill(getpid(), SIGKILL);
		if (PARENT_PID == getpid())
			write(1, "\n", 1);
		if (PARENT_PID == getpid() && PROMPT)
			put_name("minishell", ":", 1);
	}
}
