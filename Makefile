
FILES		= main utils cmd_init cmd_utils tokenizer token_init token_utils token_utils2 free signal \
				init exec env_utils env_init builtins builtins2 builtins3 builtins4 debug exec_utils  \
				exec_utils2 redir redir2 redir3 heredoc error parse_cmd
NAME		= minishell

CC			= gcc
CCFLAGS		= -I ./lib/libft/inc/ -I ./inc/ -Wall -Wextra -Werror 
MAKEFLAGS	= --no-print-directory
RLFLAGS		= -L ./lib/readline/lib -I lib/readline/include/ -lreadline
RM			= rm -rf

LIBFT_PATH	= lib/libft/
LIBFT		= $(LIBFT_PATH)libft.a

FILES_PATH	= src/
OBJ_DIR		= .obj/
RL_PATH		= ./lib/readline/
READLINE	= $(RL_PATH)lib/libreadline.a

SRCS		= $(addprefix $(FILES_PATH), $(addsuffix .c, $(FILES)))
OBJS		= $(addprefix $(OBJ_DIR), $(notdir $(SRCS:.c=.o)))
DIR			= $(shell echo $(PWD))

vpath %.c $(FILES_PATH)

all: $(READLINE) $(NAME)

$(READLINE):
	@curl -O https://ftp.gnu.org/gnu/readline/readline-8.2-rc1.tar.gz
	@tar -xvf readline-8.2-rc1.tar.gz
	@$(RM) readline-8.2-rc1.tar.gz
	@cd readline-8.2-rc1 && ./configure --prefix=$(DIR)/lib/readline && make && make install && cd ..
	@$(RM) readline-8.2-rc1

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJS)
	@$(CC) $(OBJS) $(LIBFT) $(RLFLAGS) $(CCFLAGS) -o $(NAME)
	@echo "$(GREEN)-== $(NAME) created! ==-$(DEFAULT)"

$(OBJ_DIR)%.o: %.c
	@$(CC) $(CCFLAGS) -I lib/readline/include/ -c -o $@ $< 

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR) 

$(LIBFT):
	@make $(MAKEFLAGS) -C $(LIBFT_PATH)
	
clean:
	@$(RM) $(OBJS)
	@echo "$(YELLOW)-== all object files deleted! ==-$(DEFAULT)"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(OBJ_DIR)
	@$(RM) $(RL_PATH)
	@$(RM) $(LIBFT)
	@echo "$(RED)-== all files deleted! ==-$(DEFAULT)"

libre:
	@make $(MAKEFLAGS) -C $(LIBFT_PATH) re
	@echo "$(BLUE)-== all object files recreated in libft! ==-$(DEFAULT)"

re: fclean all

.PHONY: all clean fclean libre re

# ANSI COLOR CODES
DEFAULT = \033[0m
RED     = \033[1;31m
YELLOW  = \033[1;33m
GREEN   = \033[1;32m
BLUE    = \033[1;36m
ORANGE  = \033[38;5;208m
