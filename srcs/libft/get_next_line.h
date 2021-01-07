/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vileleu <vileleu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 18:03:21 by vileleu           #+#    #+#             */
/*   Updated: 2020/10/23 17:36:39 by vileleu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef struct	s_liste
{
	int				fd;
	char			*str;
	struct s_liste	*next;
}				t_liste;

int				get_next_line(int fd, char **line);
char			**ft_strjoin_gnl(char **s1, char *s2, int i);
char			*ft_strdup_gnl(const char *s1);
t_liste			*findfd(t_liste **begin, int fd);
int				free_fd(t_liste **begin, int fd);

#endif

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

#ifndef OPEN_MAX
# define OPEN_MAX 256
#endif
