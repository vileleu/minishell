/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vileleu <vileleu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 14:36:07 by vileleu           #+#    #+#             */
/*   Updated: 2021/02/23 16:41:26 by vileleu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

void	del_ev_exit(t_o *o)
{
	t_list	*tmp;

	o->out = ft_strdup("");
	o->exit = 0;
	while (o->ev)
	{
		tmp = o->ev;
		o->ev = o->ev->next;
		free(tmp->content);
		free(tmp);
	}
}

char	*error_exit(t_o *o)
{
	ft_putstr_fd(o->name, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(o->cmd[0], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(o->cmd[1], 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd("numeric argument required", 2);
	o->fd = 2;
	del_ev_exit(o);
	return ("?=2");
}

int		full_digit(char *s)
{
	int		i;
	int		neg;

	i = -1;
	neg = 1;
	while (s[++i])
	{
		if (i == 0 && s[i] == '-')
			neg = -1;
		else if (!ft_isdigit(s[i]))
			return (0);
	}
	if (neg == -1 && i == 1)
		return (0);
	return (neg);
}

char	*ret_exit(int nb)
{
	static char	s[6];
	int			c;
	int			n;

	c = 1;
	n = nb;
	s[0] = '?';
	s[1] = '=';
	while (n > 9 && c++)
		n = n / 10;
	s[2 + c] = '\0';
	c = c + 2;
	while (--c > 1)
	{
		s[c] = (nb % 10) + '0';
		nb = nb / 10;
	}
	return (s);
}
