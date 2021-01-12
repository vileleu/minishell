/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 17:06:48 by vileleu           #+#    #+#             */
/*   Updated: 2021/01/12 13:19:28 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

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

char	**new_envp(t_o *o)
{
	char	**envp;
	t_list	*tmp;
	char	*doub;
	int		i;
	int		j;

	if (!(envp = malloc(sizeof(char*) * (ft_lstsize(o->ev) + 1))))
		return (NULL);
	i = 0;
	tmp = o->ev;
	while (tmp != NULL)
	{
		doub = ft_strdup(tmp->content);
		if (!(envp[i] = malloc(sizeof(char) * (ft_strlen(doub) + 1))))
			return (free_tab(envp, i - 1));
		j = -1;
		while (doub[++j])
			envp[i][j] = doub[j];
		envp[i++][j] = '\0';
		free(doub);
		tmp = tmp->next;
	}
	envp[i] = NULL;
	return (envp);
}
