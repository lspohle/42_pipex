NAME			= pipex

LIBFT			= libft

SRCS			= main.c \
				  execute.c \
				  exit.c \
				  special_split.c \
				  split_utils.c

OBJS			= ${SRCS:.c=.o}

CC				= cc

CFLAGS			= -Wall -Wextra -Werror -g

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
