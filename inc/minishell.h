/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 20:34:57 by emgul             #+#    #+#             */
/*   Updated: 2024/08/05 21:57:56 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
#include <stdbool.h>

#define SA_RESTART	0x10000000
#define PATH_SIZE	512

#define ARG_MAX 42

enum					e_special_char
{
	NONE,
	AND,
	OR,
	PIPE,
	REDIRECT_INPUT,
	HERE_DOC,
	REDIRECT_OUTPUT,
	APPEND_OUTPUT
};

typedef struct s_env
{
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_tokens
{
	char				*token;
	struct s_tokens		*next;
}						t_tokens;

typedef struct t_cmd
{
	char				**arr;
	int					special_char;
	struct t_cmd		*next;
	bool				is_builtin;
}						t_cmd;

typedef struct s_shell
{
	char				*line;
	int					std_input;
	t_cmd				*cmd;
	t_tokens			*tokens;
	t_env				*env;
	char				**envp;
	struct sigaction	sigint;
	struct sigaction	sigquit;
}						t_shell;

t_env					*get_env(char **env);
t_shell					*init_shell(char **env);
t_tokens				*tokenizer(char *input, t_env *env);

// UTILS
t_tokens				*new_token(char *token);
void					lstadd_back_token(t_tokens **lst, t_tokens *new);
int						ft_find_index(char *haystack, char *needle);
t_cmd					*new_cmd(char **cmd);
void					lstadd_back_cmd(t_cmd **lst, t_cmd *new);
int max_len(char *str1, char *str2);

// SIGNAL
void					handle_sigint(int signo);
void	handle_sigquit(int signo);

char					*get_special_char(char *input);

t_cmd	*create_cmd(t_tokens token);

void execute_cmd(t_shell *shell);

void init_signal(int signo, void (*handler)(int), struct sigaction *sa);
void update_value(t_env *env, char *key, char *value);
t_env *new_env(char *key, char *value);
void dollar_sign(t_shell *shell);
void handle_dollar_sign(char **cmd, t_env *env);
void	env_lstadd_back(t_env **lst, t_env *new);
char *exchange_variable(char *str, t_env *env);
bool key_exists(t_env *env, char *key);


void print_cmd(t_shell *shell);
char *get_env_value(t_env *env, char *key);

void handle_builtins(t_shell *shell);

void ft_exit(int exit_code);



// UTILS
void	execute(char *argv, char **envp);
char	*find_valid_path(char *cmd, t_env *envp);
char	*make_path(char *uncompleted_path, char *cmd);
void	free_array(char **array);

// ERROR
void	input_error(void);
void	error(char *error_message);

void execute_cmd_pipe(t_shell *shell);

#endif