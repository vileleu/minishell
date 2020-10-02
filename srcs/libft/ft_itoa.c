/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vileleu <vileleu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 11:40:52 by vileleu           #+#    #+#             */
/*   Updated: 2019/10/14 12:47:53 by vileleu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	countchar(int n)
{
	int				count;
	unsigned int	nb;

	count = 1;
	if (n < 0)
	{
		count++;
		nb = (unsigned int)-n;
	}
	else
		nb = (unsigned int)n;
	while (nb / 10 > 0)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}

char		*ft_itoa(int n)
{
	int				i;
	char			*tab;
	unsigned int	nb;

	i = countchar(n);
	if (!(tab = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	if (n < 0)
	{
		nb = (unsigned int)-n;
		tab[0] = '-';
	}
	else
		nb = (unsigned int)n;
	tab[i] = '\0';
	i--;
	while (i >= 0)
	{
		tab[i] = nb % 10 + 48;
		nb = nb / 10;
		if (nb == 0)
			break ;
		i--;
	}
	return (tab);
}
