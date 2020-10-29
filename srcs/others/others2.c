/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vileleu <vileleu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 17:06:48 by vileleu           #+#    #+#             */
/*   Updated: 2020/10/24 19:45:26 by vileleu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_strcmp_eg(char *s1, char *s2)
{
	int		i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] != '=' && s2[i] != '=')
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	if ((s1[i] == '=' && s2[i] == '\0') || (s1[i] == '\0' && s2[i] == '=') \
	|| (s1[i] == '=' && s2[i] == '+') || (s1[i] == '+' && s2[i] == '=') \
	|| (s1[i] == '+' && s2[i] == '\0') || (s1[i] == '\0' && s2[i] == '+') \
	|| s1[i] == s2[i])
		return (0);
	return (1);
}

int		ft_strcmp_ev(char *s1, char *s2)
{
	int		i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	if ((s1[i] == '=') && (s2[i] < 'a' || s2[i] > 'z') \
	&& (s2[i] < 'A' || s2[i] > 'Z') && \
	(s2[i] < '0' || s2[i] > '9') && s2[i] != '_' && i != 0)
		return (0);
	return (1);
}

char	*modif_str(char *s)
{
	char	*new;
	int		i;
	int		j;

	if (!(new = malloc(sizeof(char) * ft_strlen(s))))
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != '+')
			new[j++] = s[i++];
		else
			i++;
	}
	new[j] = '\0';
	free(s);
	return (new);
}

int		ft_strlen_ev(char *s)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (s[i] != '=' && s[i])
		i++;
	if (s[i] == '=')
		i++;
	while (s[i + len])
		len++;
	return (len);
}
