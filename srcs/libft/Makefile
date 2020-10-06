SRCS		= ft_itoa.c ft_memccpy.c ft_split.c ft_strrchr.c ft_memchr.c \
			ft_strchr.c ft_strtrim.c ft_atoi.c ft_memcmp.c ft_strdup.c \
			ft_substr.c ft_bzero.c ft_memcpy.c ft_strjoin.c ft_tolower.c \
			ft_calloc.c ft_memmove.c ft_strlcat.c ft_toupper.c ft_isalnum.c \
			ft_memset.c ft_strlcpy.c ft_isalpha.c ft_putchar_fd.c ft_strlen.c \
			ft_isascii.c ft_putendl_fd.c ft_strmapi.c ft_isdigit.c ft_putnbr_fd.c \
			ft_strncmp.c ft_isprint.c ft_putstr_fd.c ft_strnstr.c ft_putstr_free.c \
			ft_lstnew.c ft_lstsize.c ft_lstiter.c ft_lstdelone.c ft_lstclear.c \
			ft_lstadd_front.c ft_lstadd_back.c ft_lstmap.c ft_lstlast.c get_next_line.c \
			get_next_line_utils.c ft_strjoin_sp.c ft_split_m.c

OBJS		= ${SRCS:.c=.o}

NAME		= libft.a

HEADERS		= ./

FLAGS		= -Wall -Wextra -Werror

.c.o:		
			gcc ${FLAGS} -I ${HEADERS} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			@ar rc ${NAME} ${OBJS}

all:		${NAME}

clean:
			@rm -f ${OBJS}

fclean:		clean
			@rm -f ${NAME}

re:			fclean all

.PHONY:		clean fclean re all bonus
