# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/07 09:44:14 by emgul             #+#    #+#              #
#    Updated: 2024/07/31 10:39:08 by emgul            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

FILES				=	ft_atoi ft_bzero ft_calloc ft_isalnum ft_isalpha ft_isascii ft_isdigit ft_isprint ft_itoa ft_memchr \
					ft_memcmp ft_memcpy ft_memmove ft_memset ft_putchar_fd ft_putendl_fd ft_putnbr_fd ft_putstr_fd ft_split \
					ft_strchr ft_strdup ft_striteri ft_strjoin ft_strlcat ft_strlcpy ft_strlen ft_strmapi ft_strncmp ft_strnstr \
					ft_strrchr ft_strtrim ft_substr ft_tolower ft_toupper gnl/get_next_line gnl/get_next_line_utils printf/ft_printf \
					printf/ft_format_utilities printf/ft_puthex printf/ft_putnbr printf/ft_putstr printf/ft_putptr printf/ft_putunsigned

BONUS_FILES			= ft_lstiter ft_lstlast ft_lstmap ft_lstnew ft_lstsize ft_lstadd_back ft_lstadd_front ft_lstclear ft_lstdelone

NAME				= libft.a
BONUS_NAME			= libft_bonus.a

CC					= gcc
CCFLAGS				= -Wall -Wextra -Werror
MAKEFLAGS			= --no-print-directory
AR					= ar rcs
RM					= rm -rf

FILES_PATH			= src/
GNL_PATH			= src/gnl/
PRINTF_PATH			= src/printf/

OBJ_DIR				= .obj/

SRCS				= $(addprefix $(FILES_PATH), $(addsuffix .c, $(FILES)))
BONUS_SRCS			= $(addprefix $(FILES_PATH), $(addsuffix .c, $(BONUS_FILES)))

OBJS				= $(addprefix $(OBJ_DIR), $(notdir $(SRCS:.c=.o)))
BONUS_OBJS			= $(addprefix $(OBJ_DIR), $(notdir $(BONUS_SRCS:.c=.o)))

vpath %.c $(FILES_PATH) $(GNL_PATH) $(PRINTF_PATH)

all: $(OBJ_DIR) $(NAME)

bonus: $(OBJ_DIR) $(BONUS_NAME)

$(NAME): $(OBJS)
	@$(AR) $@ $^
	@echo "$(GREEN)-== $(NAME) created! ==-$(DEFAULT)"

$(BONUS_NAME): $(OBJS) $(BONUS_OBJS)
	@$(AR) $@ $^
	@echo "$(GREEN)-== $(BONUS_NAME) created! ==-$(DEFAULT)"

$(OBJ_DIR)%.o: %.c
	@echo "Compiling $< to $@"
	@$(CC) $(CCFLAGS) -c -o $@ $<

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

check-norm: all
	@norminette src/ lib/libft inc/ | grep -B 1 "Error\|Warning" || echo "$(GREEN)Norme check passed!$(DEFAULT)"
	
clean:
	@$(RM) $(OBJS)
	@$(RM) $(BONUS_OBJS)
	@echo "$(YELLOW)-== all object files deleted! ==-$(DEFAULT)"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(BONUS_NAME)
	@$(RM) $(OBJ_DIR)
	@echo "$(RED)-== all files deleted! ==-$(DEFAULT)"

re: fclean all

re-bonus: fclean bonus

.PHONY: all bonus clean fclean re re-bonus check-norm

# ANSI COLOR CODES
DEFAULT = \033[0m
RED     = \033[1;31m
YELLOW  = \033[1;33m
GREEN   = \033[1;32m
BLUE    = \033[1;36m
ORANGE  = \033[38;5;208m