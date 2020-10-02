/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vileleu <vileleu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 15:27:50 by vileleu           #+#    #+#             */
/*   Updated: 2019/11/22 12:14:19 by vileleu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*list;
	t_list	*temp;

	if (!lst)
		return ;
	list = *lst;
	while (list != NULL)
	{
		temp = list;
		list = list->next;
		ft_lstdelone(temp, del);
	}
	*lst = NULL;
}
