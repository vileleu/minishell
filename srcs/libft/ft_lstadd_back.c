/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vileleu <vileleu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 14:19:42 by vileleu           #+#    #+#             */
/*   Updated: 2019/10/21 16:24:22 by vileleu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*l;

	if (!new || !alst)
		return ;
	l = ft_lstlast(*alst);
	if (l)
		l->next = new;
	else
		*alst = new;
}
