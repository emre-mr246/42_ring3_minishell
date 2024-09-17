/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 20:34:57 by emgul             #+#    #+#             */
/*   Updated: 2024/09/17 17:50:10 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdbool.h>

#include <stdio.h>

# define PATH_SIZE 512

# define ARG_MAX 42
# define BUFFER_SIZE 4096

# define HEREDOC_TMP_PATH ".heredoc_tmp_424242"

enum					e_error
{
	ERR_NOCMD,
	ERR_ENVNAME,
	ERR_NODIR,
	ERR_CD_PWD,
	ERR_EXCBUFF,
	ERR_MEMALLOC,
	ERR_NONNUM,
	ERR_NOPERM,
	ERR_ISDIR,
	ERR_QUOTES,
	ERR_MANYARGS,
	ERR_SYNTAX
};

enum					e_redirection
{
	NONE_REDIR,
	REDIRECT_INPUT,
	HERE_DOC,
	REDIRECT_OUTPUT,
	APPEND_OUTPUT
};

enum					e_special_char
{
	NONE,
	AND,
	OR,
	PIPE
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
	bool				is_single_quote;
}						t_tokens;

typedef struct t_cmd
{
	char				**arr;
	int					special_char;
	int					out_redir;
	int					in_redir;
	char				*outfile;
	char				*infile;
	struct t_cmd		*next;
	bool				is_builtin;
	bool				is_single_quote;
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
	int					*last_exit_status;
}						t_shell;

// BUILTINS
void					handle_builtins(t_shell *shell, t_cmd *cmd);
void					handle_builtins_main(t_shell *shell, t_cmd *cmd);
void					ft_export(t_shell *shell, t_cmd *cmd);
void					ft_unset(t_shell *shell, t_cmd *cmd);
void					ft_cd(t_shell *shell, t_cmd *cmd);

// CMD
t_cmd					*create_cmds(t_shell *shell, t_tokens *token);
t_cmd					*new_cmd(char **cmd);
void					lstadd_back_cmd(t_cmd **lst, t_cmd *new);
void					check_odd_quotes(t_shell *shell, char *token);
int						get_special_char_enum(char *input);

//EXEC
void	handle_cmd_errors(t_shell *shell, t_cmd *cmd);

t_env					*get_env(char **env);
t_shell					*init_shell(char **env);
t_tokens				*tokenizer(t_shell *shell, char *input, t_env *env);

// UTILS
t_tokens				*new_token(char *token);
void					lstadd_back_token(t_tokens **lst, t_tokens *new);
int						ft_find_index(char *haystack, char *needle);
int						higher_len(char *str1, char *str2);

// SIGNAL
void					handle_sigint(int signo);
void	handle_sigquit(int signo);

char					*get_special_char(char *input);

void					execute_cmd(t_shell *shell);

void					init_signal(int signo, void (*handler)(int),
							struct sigaction *sa);
void					redirect_files(t_shell *shell, t_cmd *cmd);
void					update_value(t_env *env, char *key, char *value);
t_env					*new_env(char *key, char *value);
void					dollar_sign(t_shell *shell);
void					env_lstadd_back(t_env **lst, t_env *new);
char					*exchange_variable(char *str, t_shell *shell);
bool					key_exists(t_env *env, char *key);

void					print_cmd(t_shell *shell);
char					*get_env_value(t_env *env, char *key);

void					ft_exit(t_shell *shell, int exit_code);

void	child_signal_handler(int signum);

// UTILS
void					execute(char *argv, char **envp);
char	*find_valid_path(t_shell *shell, char *cmd, t_env *envp);
char	*make_path(t_shell *shell, char *uncompleted_path, char *cmd);
void					free_array(char **array);

void free_all(t_shell *shell);
// ERROR
void					input_error(void);
void					error(char *error_message);

void					execute_cmd(t_shell *shell);
int						cmd_len(t_cmd *cmd);

char					*find_valid_path(t_shell *shell, char *cmd, t_env *envp);

void					remove_redirs(t_shell *shell, t_cmd *cmd);
int						open_outfile(t_shell *shell, t_cmd *cmd);
int						open_infile(t_shell *shell, t_cmd *cmd);

void					print_error(t_shell *shell, char *str,
							int mode, int exits);
void					handle_builtins_main(t_shell *shell, t_cmd *cmd);
char					*parse_file(t_shell *shell, t_cmd *cmd, char *file);

char					*get_env_key(char *str);

void free_token(t_tokens *token);
void	redirect_pipes(t_cmd *cmd, int fd[][2], int cmdlen, int i);
void	close_all_fds(int fd[][2], int cmdlen);
int	is_main_builtin(t_shell *shell, t_cmd *cmd);
void	close_fds(int fd[][2], int cmdlen, int cmd_i);

void redir_heredoc(t_shell *shell, t_cmd *cmd);
void	heredoc(t_cmd *cmd);
void	remove_redirs(t_shell *shell, t_cmd *cmd);
void	remove_redir(t_shell *shell, t_cmd *cmd, char **arr);
int	write_to_redir(t_shell *shell, t_cmd *cmd, int *i, int mode_in_out);

int	infile_controls(t_shell *shell, t_cmd *cmd);
int	outfile_controls(t_shell *shell, t_cmd *cmd);
int	open_infile(t_shell *shell, t_cmd *cmd);
int	open_outfile(t_shell *shell, t_cmd *cmd);
int	get_redirection(char *s);

void	parse_cmds(t_shell *shell);
char	*allocate_str(t_shell *shell, int buff_size);

void skip_quotes(char **str, int *i);
void	skip_whitespaces(char **str, int *i);
char	*handle_quote(char **str, char quote);
char	*handle_comment(char *str);
void	print_token(t_tokens *token);

#endif