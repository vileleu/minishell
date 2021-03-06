/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_m.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 11:39:48 by vileleu           #+#    #+#             */
/*   Updated: 2021/03/10 16:07:40 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

/*
** fonction qui split la commande en token en
** supprimant les ' , les " et en ecrivant les EV
*/

int		countwords(t_o *o, char *str, char c, int nb)
{
	int		i;
	char	m;

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
					while (str[i] != m && str[i])
						i++;
				}
				delete_ev(o, str, &i, &nb);
			}
		}
		else
			i++;
	}
	return (nb);
}

int		sizeword(char *str, int *i, char c, t_o *o)
{
	int		j;
	int		res;
	int		ver;

	res = 0;
	ver = 1;
	j = *i;
	while (str[j] != c && str[j])
	{
		res += sizeword_bis(o, str, &j, &ver);
		if (str[j] == '$')
			res += size_ev(str + j, o, 0);
		if (str[j] == '\\')
		{
			j++;
			res--;
		}
		j++;
	}
	res += j - *i;
	return (res - ((ver - 1) * 2));
}

int		loop_split_ev(char **s, char *str, int *size, t_o *o)
{
	if (!(loop_split_ev_bis(s, str, size, o)))
		return (0);
	if (enter_quote(*s, *size))
	{
		if (!(loop_split_ev_norme(o, s, str, size)))
			return (0);
		(*size)++;
	}
	return (1);
}

char	*loop_split(char **s, int *size, char c, t_o *o)
{
	int		len;
	char	*str;

	while ((*s)[*size] == c && (*s)[*size])
		(*size)++;
	delete_after(o, *s, size);
	len = sizeword(*s, size, c, o);
	if (!(str = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while ((*s)[*size] && (*s)[*size] != c)
	{
		if (!(loop_split_ev(s, str, size, o)))
			return (NULL);
		little_norme(o, s, str, size);
		if (((*s)[*size] && (*s)[*size] == '$' &&
			!ft_isalnum((*s)[*size + 1])) || ((*s)[*size] && (*s)[*size] != c &&
			(*s)[*size] != '$' && (*s)[*size] != '\\' &&
			(*s)[*size] != '\'' && (*s)[*size] != '\"'))
			str[(o->i)++] = (*s)[(*size)++];
	}
	str[o->i] = '\0';
	o->i = 0;
	return (str);
}

char	**ft_split_m(char **s, char c, t_o *o)
{
	char	**news;
	int		i;
	int		size;
	int		words;

	i = -1;
	size = 0;
	if ((words = countwords(o, *s, c, 0)) == -1)
		return (NULL);
	if (!(news = malloc(sizeof(char*) * (words + 1))))
		return (NULL);
	while (++i < words)
	{
		if (!(news[i] = loop_split(s, &size, c, o)))
			return (free_tab(news, i - 1));
	}
	news[i] = NULL;
	return (news);
}
