/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vileleu <vileleu@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/27 15:52:19 by vileleu           #+#    #+#             */
/*   Updated: 2020/10/25 18:16:42 by vileleu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include "get_next_line.h"

typedef struct	s_list
{
	void			*content;
	struct s_list	*next;
}				t_list;

/*
**FONCTIONS CONVERSION
*/

int				ft_atoi(const char *str);
char			*ft_itoa(int n);

/*
** FONCTIONS MEM
*/

void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memset(void *b, int c, size_t len);

/*
** FONCTIONS VERIFICATION CARACTERES
*/

int				ft_isalnum(int c);
int				ft_isalpha(int c);
int				ft_isascii(int c);
int				ft_isdigit(int c);
int				ft_isprint(int c);
int				ft_tolower(int c);
int				ft_toupper(int c);

/*
**FONCTIONS CREATION DE CHAINES
*/

char			*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void			*ft_calloc(size_t count, size_t size);
char			*ft_strdup(const char *s1);

/*
**MANIPULATION DE FICHIERS
*/

void			ft_putstr(char *s);
void			ft_putstr_free(char *s, int fd);
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putendl_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);

/*
**FONCTIONS GESTION DE CHAINES
*/

void			ft_bzero(void *s, size_t n);
char			**ft_split(char const *s, char c);
char			**ft_split_s(char const *s, char c);
int				enter_slash(const char *line, int i, char c);
char			*ft_strchr(const char *s, int c);
char			*ft_strjoin(char *s1, char const *s2);
char			*ft_strjoin_sp(char *s1, char const *s2, char sp);
size_t			ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);
size_t			ft_strlen(const char *s);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
char			*ft_strnstr(const char *haystack, const char *needle, \
				size_t len);
char			*ft_strrchr(const char *s, int c);
char			*ft_strtrim(char const *s1, char const *set);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			**free_tab(char **tab, int i);

/*
**FONCTIONS LISTES CHAÎNÉES
*/

t_list			*ft_lstnew(void const *content);
void			ft_lstadd_front(t_list **alst, t_list *new);
int				ft_lstsize(t_list *lst);
t_list			*ft_lstlast(t_list *lst);
void			ft_lstadd_back(t_list **alst, t_list *new);
void			ft_lstdelone(t_list *lst, void (*del)(void *));
void			ft_lstclear(t_list **lst, void (*del)(void *));
void			ft_lstiter(t_list *lst, void (*f)(void *));
t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), \
				void (*del)(void *));

#endif
