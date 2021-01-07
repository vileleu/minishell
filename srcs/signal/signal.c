/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vico <vico@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 17:06:48 by vileleu           #+#    #+#             */
/*   Updated: 2020/12/03 21:16:18 by vico             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
