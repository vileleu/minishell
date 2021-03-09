/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_s.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vileleu <vileleu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 11:39:48 by vileleu           #+#    #+#             */
/*   Updated: 2021/03/09 16:24:34 by vileleu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		enter_slash(const char *line, int i, char c)
{
	int		j;
	int		co;

	if (!i)
	{
		if (line[i] == c)
			return (1);
		return (0);
	}
	j = i - 1;
	co = 0;
	while (j >= 0 && line[j] == '\\')
	{
		j--;
		c++;
	}
	if (line[i] == c && co % 2 == 0)
		return (1);
	return (0);
}

static unsigned int	countwords(const char *str, char c, int nb)
{
	unsigned int	i;
	char			m;

	i = 0;
	while (str[i] != '\0')
	{
		if (!enter_slash(str, i, c))
		{
			nb++;
			while (!enter_slash(str, i, c) && str[i] != '\0')
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
	while (!enter_slash(str, *i, c) && str[*i])
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

	while (enter_slash(s, *size, c) && s[*size])
		(*size)++;
	if (!(str = malloc(sizeof(char) * (sizeword(s, size, c) + 1))))
		return (NULL);
	j = 0;
	while (s[*size] && !enter_slash(s, *size, c))
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
