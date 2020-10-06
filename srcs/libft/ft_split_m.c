/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_m.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vileleu <vileleu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 11:39:48 by vileleu           #+#    #+#             */
/*   Updated: 2020/10/06 19:00:01 by vileleu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	countwords(const char *str, char c, int nb)
{
	unsigned int	i;
	char			m;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
		{
			nb++;
			while (str[i] != c && str[i] != '\0')
			{
				if (str[i] == '\"' || str[i] == '\'')
				{
					m = str[i++];
					while (str[i] != m && str[i] != '\0')
						i++;
				}
				i++;
			}
		}
		else
			i++;
	}
	return (nb);
}

static unsigned int	sizeword(const char *str, int *i, char c)
{
	int		prev;
	int		res;
	int		ver;
	char	m;

	ver = 0;
	prev = *i;
	while (str[*i] != c && str[*i] != '\0')
	{
		if (str[*i] == '\"' || str[*i] == '\'')
		{
			m = str[(*i)++];
			ver++;
			while (str[*i] != m && str[*i] != '\0')
				(*i)++;
		}
		(*i)++;
	}
	res = *i - prev;
	*i = prev;
	return (res - (ver * 2));
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

char				*loop_split(char const *s, int *size, char c)
{
	int		j;
	char	m;
	char	*str;

	while (s[*size] == c && s[*size])
		(*size)++;
	if (!(str = malloc(sizeof(char) * (sizeword(s, size, c) + 1))))
		return (NULL);
	j = 0;
	while (s[*size] && s[*size] != c)
	{
		if (s[*size] == '\"' || s[*size] == '\'')
		{
			m = s[(*size)++];
			while (s[*size] != m && s[*size] != '\0')
				str[j++] = s[(*size)++];
			(*size)++;
		}
		else
			str[j++] = s[(*size)++];
	}
	str[j] = '\0';
	return (str);
}

char				**ft_split_m(char const *s, char c)
{
	char	**news;
	int		i;
	int		size;
	int		words;

	i = 0;
	size = 0;
	if (s == NULL)
		return (NULL);
	words = countwords(s, c, 0);
	if (!(news = malloc(sizeof(char*) * (words + 1))))
		return (NULL);
	while (i < words)
	{
		if (!(news[i] = loop_split(s, &size, c)))
			return (free_tab(news, i - 1));
		i++;
	}
	news[i] = NULL;
	return (news);
}
