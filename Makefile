# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/11 07:09:36 by emgul             #+#    #+#              #
#    Updated: 2024/06/22 20:38:14 by emgul            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES			=	main \
					env

NAME			=	minishell

CC				=	gcc
CFLAGS			=	-I $(LIBFT_PATH) -g # -Wall -Wextra -Werror
MFLAGS			=	-s -C
AR				=	ar rcs
RM				=	rm -rf

LIBFT_PATH		=	lib/libft/
LIBFT			=	$(LIBFT_PATH)libft.a

FILES_PATH		=	src/

SRCS            =   $(addprefix $(FILES_PATH), $(addsuffix .c, $(FILES)))

OBJS            =   $(SRCS:.c=.o)

VALGRIND_PARAMS	=	--leak-check=full --show-leak-kinds=all --track-origins=yes

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

$(NAME): $(LIBFT) $(OBJS)
	@gcc $(OBJS) -o $(NAME) $(LIBFT) -lXext -lX11 -lm -lbsd
	@echo "$(GREEN)-== $(NAME) created! ==-$(DEFAULT)"
	@make --no-print-directory clean

$(LIBFT):
	@make --no-print-directory $(MFLAGS) $(LIBFT_PATH)

check-leaks: all
	@make --no-print-directory re
	@echo "$(RED)-==/ LEAK CHECK MODE ON \==-$(DEFAULT)"
	@valgrind $(VALGRIND_PARAMS) ./fdf maps/10-2.fdf
	@make --no-print-directory clean

all: $(NAME)

clean:
	@$(RM) $(OBJS)
	@$(RM) $(BONUS_OBJS)
	@echo "$(YELLOW)-== all object files deleted! -==$(DEFAULT)"

fclean: clean libclean
	@$(RM) $(NAME)
	@echo "$(RED)-== all files deleted! -==$(DEFAULT)"

libclean:
	@make $(MFLAGS) $(LIBFT_PATH) fclean
	@echo "$(BLUE)-== all object files deleted in libraries! -==$(DEFAULT)"

re: fclean all

re-bonus: fclean bonus

.PHONY: all clean fclean re bonus check-leak libclean

# ANSI COLOR CODES
DEFAULT = \033[0m
RED = \033[1;31m
YELLOW = \033[1;33m
GREEN = \033[1;32m
BLUE = \033[1;36m
ORANGE = \033[38;5;208m
