/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 20:34:57 by emgul             #+#    #+#             */
/*   Updated: 2024/07/10 23:09:41 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <signal.h>

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

typedef struct s_shell
{
	char				*line;
	int					std_input;
	t_tokens			*tokens;
	t_env				*env;
	struct sigaction	sigint;
	struct sigaction	sigquit;
}						t_shell;

t_env					*get_env(char **env);
t_shell					*init_shell(char **env);
t_tokens				*tokenizer(char *input, t_env *env);

// UTILS
t_tokens				*new_token(char *token);
void					lstadd_back_token(t_tokens **lst, t_tokens *new);

// SIGNAL
void					handle_sigint(int signo);

#endif