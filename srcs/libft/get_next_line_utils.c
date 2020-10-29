/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vileleu <vileleu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 18:03:30 by vileleu           #+#    #+#             */
/*   Updated: 2020/10/23 17:17:26 by vileleu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup_gnl(const char *s1)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	j = 0;
	while (s1[j])
		j++;
	if (!s1 || !(ptr = malloc((j + 1) * sizeof(char))))
		return (NULL);
	i = 0;
	while (i < j)
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

char	**ft_strjoin_gnl(char **s1, char *s2, int i)
{
	char	*temp;
	int		len1;
	int		len2;

	len1 = 0;
	while ((*s1)[len1])
		len1++;
	len2 = i;
	if (!(temp = ft_strdup_gnl(*s1)))
		return (NULL);
	free(*s1);
	if (!(*s1 = malloc(sizeof(char) * (len1 + len2 + 1))))
		return (NULL);
	i = -1;
	while (++i < len1)
		(*s1)[i] = temp[i];
	free(temp);
	i = -1;
	while (++i < len2)
		(*s1)[len1 + i] = s2[i];
	(*s1)[len1 + len2] = '\0';
	return (s1);
}

int		free_fd(t_liste **begin, int fd)
{
	t_liste	*tmp;
	t_liste	*lst;

	tmp = NULL;
	lst = *begin;
	while (*begin != NULL)
	{
		if ((*begin)->fd == fd)
		{
			if (tmp)
				tmp->next = (*begin)->next;
			else
				lst = lst->next;
			tmp = (*begin)->next;
			free(*begin);
			*begin = tmp;
		}
		else
		{
			tmp = *begin;
			*begin = (*begin)->next;
		}
	}
	*begin = lst;
	return (0);
}

t_liste	*create_elem(int fd)
{
	t_liste	*lst;

	if (!(lst = malloc(sizeof(t_liste))))
		return (NULL);
	lst->fd = fd;
	lst->str = NULL;
	lst->next = NULL;
	return (lst);
}

t_liste	*findfd(t_liste **begin, int fd)
{
	t_liste	*lst;

	if (fd > OPEN_MAX || fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	lst = *begin;
	while (lst != NULL)
	{
		if (lst->fd == fd)
			return (lst);
		if (lst->next == NULL)
			break ;
		lst = lst->next;
	}
	if (*begin)
	{
		lst->next = create_elem(fd);
		lst = lst->next;
		return (lst);
	}
	else
	{
		*begin = create_elem(fd);
		return (*begin);
	}
}
