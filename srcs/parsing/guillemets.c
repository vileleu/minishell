/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   guillemets.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thoberth <thoberth@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/04 15:11:21 by vileleu           #+#    #+#             */
/*   Updated: 2021/01/12 13:19:43 by thoberth         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

char	*get_newline(char *line)
{
	char	*newline;

	put_name("> ", "", 1);
	if ((get_next_line(0, &newline)) < 0)
		return (NULL);
	if (!(line = ft_strjoin_sp(line, newline, '\n')))
		return (NULL);
	free(newline);
	return (line);
}

void	quote_bbis(char *line, int *i, char c, int *comp)
{
	while (line[*i])
	{
		if (line[*i] == c)
		{
			(*comp)++;
			(*i)++;
			break ;
		}
		(*i)++;
	}
}

int		quote_bis(char *line)
{
	int		i;
	int		comp;
	char	c;

	i = 0;
	comp = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'')
		{
			comp++;
			c = line[i++];
			quote_bbis(line, &i, c, &comp);
		}
		else
			i++;
	}
	return (comp);
}

char	*quote(char *line)
{
	int		comp;

	comp = 1;
	while (comp == 1)
	{
		comp = 0;
		comp = quote_bis(line);
		if (comp % 2 == 1)
		{
			if (!(line = get_newline(line)))
				return (NULL);
		}
	}
	return (line);
}
