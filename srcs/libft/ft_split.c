/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vileleu <vileleu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 11:39:48 by vileleu           #+#    #+#             */
/*   Updated: 2020/10/02 15:01:03 by vileleu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	countwords(const char *str, char c)
{
	unsigned int	nb;
	unsigned int	i;

	nb = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			nb++;
			while (str[i] != c && str[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (nb);
}

static unsigned int	sizeword(const char *str, char c)
{
	unsigned int	i;

	i = 0;
	while (str[i] != c && str[i] != '\0')
		i++;
	return (i);
}

static char			**free_tab(char **tab, int i)
{
	while (i >= 0)
	{
		free(tab[i]);
		i--;
	}
	free(tab);
	return (NULL);
}

char				**ft_split(char const *s, char c)
{
	char			**news;
	unsigned int	i;
	unsigned int	j;
	unsigned int	size;

	i = 0;
	size = 0;
	if (s == NULL)
		return (NULL);
	if (!(news = malloc(sizeof(char*) * (countwords(s, c) + 1))))
		return (NULL);
	while (i < countwords(s, c))
	{
		ft_putchar_fd(i + 48, 1);
		while (s && s[size] == c)
			size++;
		if (!(news[i] = malloc(sizeof(char) * (sizeword(s + size, c) + 1))))
			return (free_tab(news, i - 1));
		j = 0;
		while (s && s[size] != c)
			news[i][j++] = s[size++];
		news[i][j] = '\0';
		i++;
	}
	news[i] = NULL;
	return (news);
}
