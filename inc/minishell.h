/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 20:34:57 by emgul             #+#    #+#             */
/*   Updated: 2024/09/25 15:14:20 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>
# include <stdbool.h>

# define ARG_MAX 1024
# define BUFFER_SIZE 2048

# define HEREDOC_TMP_PATH ".heredoc_tmp_424242"

typedef struct s_shell	t_shell;

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
}						t_tokens;

typedef struct t_cmd
{
	char				**arr;
	int					special_char;
	int					out_redir;
	int					in_redir;
	char				*outfile;
	char				*infile;
	char				**heredoc_arr;
	struct t_cmd		*next;
	bool				is_builtin;
	t_shell				*shell;
}						t_cmd;

typedef struct s_shell
{
	char				*line;
	t_cmd				*cmd;
	t_tokens			*tokens;
	t_env				*env;
	char				**envp;
	struct sigaction	sigint;
	struct sigaction	sigquit;
	int					*exit_status;
}						t_shell;

// BUILTINS
void					handle_builtins(t_shell *shell, t_cmd *cmd);
void					ft_cd(t_shell *shell, t_cmd *cmd);

// BUILTINS2
void					ft_export(t_shell *shell, t_cmd *cmd);
int						is_main_builtin(t_cmd *cmd);
void					key_valid(t_shell *shell, char *key);

// BUILTINS3
void					handle_builtins_main(t_shell *shell, t_cmd *cmd);
void					ft_exit(int exit_code);

// BUILTINS4
void					ft_unset_key(t_shell *shell, char *key);
int						is_builtin(t_cmd *cmd);

// CMD_INIT
void					lstadd_back_cmd(t_cmd **lst, t_cmd *new);
t_cmd					*new_cmd(t_shell *shell, char **arr);
t_cmd					*create_cmds(t_shell *shell, t_tokens token);

// CMD_UTILS
int						check_odd_quotes(t_shell *shell, char *token);
int						get_special_char_enum(char *input);
int						cmd_len(t_cmd *cmd);

// ENV_INIT
void					env_lstadd_back(t_env **lst, t_env *new);
t_env					*new_env(char *key, char *value);
void					get_value(char *str, t_env *vars);
t_env					*get_env(char **env);


// ENV_UTILS
void					update_value(t_env *env, char *key, char *value);
bool					key_exists(t_env *env, char *key);
char					*get_env_key(char *str);
char					*get_env_value(t_env *env, char *key);

// ERROR
void					print_error(t_shell *shell, char *str, int mode, int exits);

// EXEC_UTILS
char					*make_path(char *uncompleted_path, char *cmd);
char					*find_valid_path(char *cmd, t_env *envp);
void					close_fds(int fd[][2], int cmdlen, int cmd_i);
void					handle_cmd_errors(t_shell *shell, t_cmd *cmd);
void					wait_for_pids(t_shell *shell);

// EXEC
int						child_process(t_shell *shell, t_cmd *cmd, char *path);
void					run_cmds(t_shell *shell, int fd[][2], int cmdlen);
void					execute_cmd(t_shell *shell);

// INIT
void					init_signal(int signo, void (*handler)(int),
							struct sigaction *sa);
t_shell					*init_shell(char **env);

// PARSE_CMD
void					parse_cmds(t_shell *shell);

// REDIR
void					redirect_files(t_shell *shell, t_cmd *cmd);
void					redirect_pipes(int fd[][2], int cmdlen,
							int i);
void					close_all_fds(int fd[][2], int cmdlen);
char					*parse_file(t_shell *shell, char *file);

// REDIR2
int						get_redirection(char *s);
int						open_outfile(t_shell *shell, t_cmd *cmd);
int						open_infile(t_cmd *cmd);
int						outfile_controls(t_shell *shell, t_cmd *cmd);
int						infile_controls(t_shell *shell, t_cmd *cmd);

// REDIR3
int						write_to_redir(t_shell *shell, t_cmd *cmd, int *i,
							int mode_in_out);
void					remove_redir(t_shell *shell, t_cmd *cmd, char **arr);
void					remove_redirs(t_shell *shell, t_cmd *cmd);

// HEREDOC
void					heredoc(t_cmd *cmd);
void					redir_heredoc(void);
void					add_to_heredoc_arr(t_cmd *cmd, char *str);

// SIGNAL
void					handle_sigint(int signo);
void					handle_sigquit(int signo);
void					child_signal_handler(int signum);

// TOKEN_INIT
t_tokens				*new_token(char *token);
void					lstadd_back_token(t_tokens **lst, t_tokens *new);
void					free_token(t_tokens *token);

// TOKEN_UTILS
char					*handle_comment(char *str);
int						handle_quote(char **res, char **str, char quote);
void					skip_whitespaces(char **str, int *i);
void					skip_quotes(char **str, int *i);
char					*get_special_char(char *input);
int						check_syntax(t_shell *shell, t_tokens *token);
int						get_indexes(char *input);

// TOKENIZER
int						handle_special_char(char **res, char **input);
t_tokens				*tokenizer(t_shell *shell, char *input, t_env *env);

// TOKENIZER2
void					handle_space(char **res, char **str);

// UTILS
int						ft_find_index(char *haystack, char *needle);
int						higher_len(char *str1, char *str2);
char					*allocate_str(t_shell *shell, int buff_size);
int						str_in_array(char **arr, char *str);

// FREE
void					free_array(char **arr);
void					free_cmd(t_cmd *cmd);
void					free_cmds(t_shell *shell);
void					free_all(t_shell *shell);
void					free_env(t_env *env);

// DEBUG
void					print_cmd(t_shell *shell);
void					print_token(t_tokens *token);

#endif