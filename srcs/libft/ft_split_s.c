/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vileleu <vileleu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 11:39:48 by vileleu           #+#    #+#             */
/*   Updated: 2020/10/25 17:55:40 by vileleu          ###   ########.fr       */
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
	char	m;

	prev = *i;
	while (str[*i] != c && str[*i] != '\0')
	{
		if (str[*i] == '\"' || str[*i] == '\'')
		{
			m = str[(*i)++];
			while (str[*i] != m && str[*i] != '\0')
				(*i)++;
		}
		(*i)++;
	}
	res = *i - prev;
	*i = prev;
	return (res);
}

char				*loop_split_s(char const *s, int *size, char c)
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
			m = s[*size];
			str[j++] = s[(*size)++];
			while (s[*size] != m && s[*size] != '\0')
				str[j++] = s[(*size)++];
			str[j++] = s[(*size)++];
		}
		else
			str[j++] = s[(*size)++];
	}
	str[j] = '\0';
	return (str);
}

char				**ft_split_s(char const *s, char c)
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
		if (!(news[i] = loop_split_s(s, &size, c)))
			return (free_tab(news, i - 1));
		i++;
	}
	news[i] = NULL;
	return (news);
}
