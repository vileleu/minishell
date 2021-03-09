/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vileleu <vileleu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 19:47:04 by vileleu           #+#    #+#             */
/*   Updated: 2021/02/23 16:10:28 by vileleu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int		for_digit(t_o *o, char **line, int *i, int v)
{
	char	*fake;

	if (!(fake = create_fake(*line, i, 1, v)))
		return (0);
	if (!(replace(line, i, fake, o)))
		return (free_all(NULL, &fake, 0));
	return (free_all(NULL, &fake, 1));
}