FILES				= main utils cmd_init cmd_utils free tokenizer tokenizer2 token_init token_utils signal init exec env_utils env_init builtins builtins2 builtins3 debug exec_utils redir redir2 redir3 error parse_cmd

NAME				= minishell

CC					= gcc
CCFLAGS				= -I /usr/local/opt/readline/include -I ./lib/libft/inc/ -I ./inc/ -g #-fsanitize=address #-Wall -Wextra -Werror 
MAKEFLAGS			= --no-print-directory
RM					= rm -rf

LIBFT_PATH			= lib/libft/
LIBFT				= $(LIBFT_PATH)libft.a

FILES_PATH			= src/mandatory/
OBJ_DIR				= .obj/

SRCS				= $(addprefix $(FILES_PATH), $(addsuffix .c, $(FILES)))
OBJS				= $(addprefix $(OBJ_DIR), $(notdir $(SRCS:.c=.o)))

vpath %.c $(FILES_PATH)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_DIR) $(OBJS)
	@$(CC) $(OBJS) $(LIBFT) -L /usr/local/opt/readline/lib -lreadline $(CCFLAGS) -o $(NAME)
	@echo "$(GREEN)-== $(NAME) created! ==-$(DEFAULT)"

$(OBJ_DIR)%.o: %.c
	@$(CC) $(CCFLAGS) -c -o $@ $<

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(LIBFT):
	@make $(MAKEFLAGS) -C $(LIBFT_PATH)

check-norm: all
	@norminette src/ lib/libft inc/ | grep -B 1 "Error\|Warning" || echo "$(GREEN)Norme check passed!$(DEFAULT)"
	
clean:
	@$(RM) $(OBJS)
	@echo "$(YELLOW)-== all object files deleted! ==-$(DEFAULT)"

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(OBJ_DIR)
	@echo "$(RED)-== all files deleted! ==-$(DEFAULT)"

libre:
	@make $(MAKEFLAGS) -C $(LIBFT_PATH) re
	@echo "$(BLUE)-== all object files deleted in libraries! ==-$(DEFAULT)"

re: fclean all

leak: re
	valgrind --suppressions=misra.supp --leak-check=full --show-leak-kinds=all --track-origins=yes ./minishell
#--trace-children=yes --track-fds=yes

test:re
	cd tester && ./tester

.PHONY: all clean fclean libre re check-norm leak test

# ANSI COLOR CODES
DEFAULT = \033[0m
RED     = \033[1;31m
YELLOW  = \033[1;33m
GREEN   = \033[1;32m
BLUE    = \033[1;36m
ORANGE  = \033[38;5;208m

#suppresssion dosyası oluşturma
#valgrind --gen-suppressions=all --leak-check=full --show-leak-kinds=all --track-origins=yes ./minishell 2> valgrind_output.txt
#awk '/^{/{f=1} f; /^}/{f=0}' valgrind_output.txt > misra.supp
