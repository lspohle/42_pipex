# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lspohle <lspohle@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/29 21:12:07 by lspohle           #+#    #+#              #
#    Updated: 2023/03/31 14:35:04 by lspohle          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			= pipex
				
LIBFT			= libft

SRCS			= mandatory/main.c \
				  mandatory/execute.c \
				  mandatory/exit.c \
				  mandatory/split.c

BSRCS			= bonus/main_bonus.c \
				  bonus/execute_bonus.c \
				  bonus/exit_bonus.c \
				  bonus/split_bonus.c \

OBJS			= ${SRCS:.c=.o}

BOBJS			= ${BSRCS:.c=.o}

CC				= cc

CFLAGS			= -Wall -Wextra -Werror 

RM				= rm -f

# Colors
GREEN			= \033[92m
YELLOW			= \033[0;33m
BLUE			= \033[0;34m
MAGENTA			= \033[0;35m
ESCAPE			= \033[0m

%.o: %.c		
				@${CC} -c $^ -o $@

${NAME}:		${OBJS} ${LIBFT}/libft.a
				@${CC} ${CFLAGS} ${OBJS} -L ${LIBFT} -lft -o ${NAME}
				@echo "${GREEN}******************  COMPILED  *******************${ESCAPE}"
				@echo "${BLUE}*** EXECUTE: ${MAGENTA}./pipex infile cmd1 cmd2 outfile ${BLUE}***${ESCAPE}"

${LIBFT}/libft.a:
				@make bonus -C ${LIBFT}		

all:			${NAME}

bonus:			${BOBJS} ${LIBFT}/libft.a
				@${CC} ${CFLAGS} ${BOBJS} -L ${LIBFT} -lft -o ${NAME}
				@echo "${GREEN}******************  COMPILED  *******************${ESCAPE}"
				@echo "${BLUE}* EXECUTE: ${MAGENTA}./pipex infile cmd1 cmd2 ... outfile ${BLUE}*${ESCAPE}"

norm:			
				@echo "-------------------------------------------------"
				@echo "${MAGENTA}******************  MANDATORY  ******************${ESCAPE}"
				@echo "-------------------------------------------------"
				@echo "${YELLOW}*****************  NORMINETTE  ******************${ESCAPE}"
				@cd ${LIBFT} && norminette
				@cd mandatory && norminette	
				@echo "${YELLOW}******************  COMPILING  ******************${ESCAPE}"

bnorm:		
				@echo "-------------------------------------------------"
				@echo "${MAGENTA}********************  BONUS  ********************${ESCAPE}"
				@echo "-------------------------------------------------"
				@echo "${YELLOW}*****************  NORMINETTE  ******************${ESCAPE}"
				@cd ${LIBFT} && norminette
				@cd bonus && norminette	
				@echo "${YELLOW}******************  COMPILING  ******************${ESCAPE}"

clean:	
				@${RM} ${OBJS}
				@${RM} ${BOBJS}
				@make clean -C ${LIBFT}
				@echo "${GREEN}*******************  CLEANED  *******************${ESCAPE}"

fclean:			clean
				@${RM} ${NAME}
				@make fclean -C ${LIBFT}

re:				fclean all

bre:			fclean bonus

.PHONY:			all bonus norm bnorm clean fclean re bre
