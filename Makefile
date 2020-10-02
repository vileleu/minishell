
BLUE = 		\033[0;34m
GREEN = 	\033[0;32m
LIGHTBLUE = \033[1;34m
RED = 		\033[0;31m
YELLOW = 	\033[1;33m
ORANGE = 	\033[0;33m
MAGENTA = 	\033[0;35m
RESET = 	\033[0m

SRCS		= srcs/main.c srcs/error.c

OBJS		= ${SRCS:.c=.o}

NAME		= minishell

LIBFT		= srcs/libft

HEADERS		= -I headers/

FLAGS		= -Wall -Wextra -Werror

.c.o:		
			@echo "${ORANGE}- $(BLUE)\c"
			gcc ${FLAGS} ${HEADERS} -I ${LIBFT} -c $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			@echo "$(ORANGE)Compiling libft : $(BLUE)"
			@make -C $(LIBFT) all
			@echo "$(ORANGE)Create executable file :"
			@echo "${ORANGE}- $(BLUE)\c"
			gcc ${FLAGS} ${OBJS} ${LIBFT}/libft.a -o ${NAME}
			@echo "$(GREEN)|||<<< minishell ready >>>|||$(RESET)"

all:		${NAME}

clean:
			@echo ""
			@echo "$(RED)Erase files '.o'"
			@make -C $(LIBFT) clean
			@rm -rf $(OBJS)
			@echo ""

fclean:
			@echo ""
			@echo "$(RED)Erase files '.o'"
			@make -C $(LIBFT) clean
			@rm -rf $(OBJS)
			@echo "$(RED)Delete executable file and libft"
			@make -C $(LIBFT) fclean
			@rm -rf ${NAME}
			@echo "$(RESET)"

re:			fclean all

.PHONY:		clean fclean re all