NAME			= pipex

LIBFT			= libft

SRCS			= main.c \
				  path.c \
				  process.c

OBJS			= ${SRCS:.c=.o}

CC				= cc

CFLAGS			= -Wall -Wextra -Werror -g -O0

RM				= rm -f

${NAME}:		${OBJS} ${LIBFT}/libft.a
				${CC} ${CFLAGS} ${OBJS} -L ${LIBFT} -lft -o ${NAME}

${LIBFT}/libft.a:
				make bonus -C ${LIBFT}

all:			${NAME}

clean:	
				${RM} ${OBJS}
				make clean -C ${LIBFT}

fclean:			clean
				${RM} ${NAME}
				make fclean -C ${LIBFT}

re:				fclean all

.PHONY:			all clean fclean re LIBFT
