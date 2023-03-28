NAME			= pipex

LIBFT			= libft

SRCS			= mandatory/main.c \
				  mandatory/execute.c \
				  mandatory/exit.c \
				  mandatory/special_split.c \
				  mandatory/split_utils.c

BSRCS			= bonus/main_bonus.c \
				  bonus/execute_bonus.c \
				  bonus/exit_bonus.c \
				  bonus/special_split_bonus.c \
				  bonus/split_utils_bonus.c

OBJS			= ${SRCS:.c=.o}

BOBJS			= ${BSRCS:.c=.o}

CC				= cc

CFLAGS			= -Wall -Wextra -Werror 

RM				= rm -f

${NAME}:		${OBJS} ${LIBFT}/libft.a
				${CC} ${CFLAGS} ${OBJS} -L ${LIBFT} -lft -o ${NAME}

${LIBFT}/libft.a:
				make bonus -C ${LIBFT}

all:			${NAME}

bonus:			${BOBJS} ${LIBFT}/libft.a
				${CC} ${CFLAGS} ${BOBJS} -L ${LIBFT} -lft -o ${NAME}

clean:	
				${RM} ${OBJS}
				${RM} ${BOBJS}
				make clean -C ${LIBFT}

fclean:			clean
				${RM} ${NAME}
				make fclean -C ${LIBFT}

re:				fclean all

bre:			fclean bonus

.PHONY:			all bonus clean fclean re bre
