/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:48:40 by emgul             #+#    #+#             */
/*   Updated: 2024/07/24 22:38:03 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../lib/libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

void ft_echo(t_shell *shell)
{
	int i;
	bool newline;

	newline = true;
	i = 1;
	if(ft_strncmp(shell->cmd->cmd[1], "-n", ft_strlen(shell->cmd->cmd[1])) == 0)
	{
		i = 2;
		newline = false;
	}
	while (shell->cmd->cmd[i])
	{
		ft_putstr_fd(shell->cmd->cmd[i], 1);
		write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
}

void handle_builtins(t_shell *shell)
{
	if(ft_strncmp(shell->cmd->cmd[0], "exit", ft_strlen(shell->cmd->cmd[0])) == 0)
        exit(EXIT_SUCCESS);
	if(ft_strncmp(shell->cmd->cmd[0], "echo", ft_strlen(shell->cmd->cmd[0])) == 0)
	{
		shell->cmd->is_builtin = true;
        ft_echo(shell);
	}
	if(ft_strncmp(shell->cmd->cmd[0], "cd", ft_strlen(shell->cmd->cmd[0])) == 0)
        exit(EXIT_SUCCESS);
	if(ft_strncmp(shell->cmd->cmd[0], "pwd", ft_strlen(shell->cmd->cmd[0])) == 0)
		exit(EXIT_SUCCESS);
	if(ft_strncmp(shell->cmd->cmd[0], "export", ft_strlen(shell->cmd->cmd[0])) == 0)
		exit(EXIT_SUCCESS);
	if(ft_strncmp(shell->cmd->cmd[0], "unset", ft_strlen(shell->cmd->cmd[0])) == 0)
		exit(EXIT_SUCCESS);
	if(ft_strncmp(shell->cmd->cmd[0], "env", ft_strlen(shell->cmd->cmd[0])) == 0)
		exit(EXIT_SUCCESS);
}

static char *get_key(char **str)
{
	int i;
	char *res;

	i = 0;
	(*str)++;
	while ((*str)[i] && (*str)[i] != '$')
		i++;
	res = ft_substr(*str, 0, i);
	*str += i;
	return(res);
}

static char *get_value(char *key, t_env *env)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(key, tmp->key, ft_strlen(key)) == 0)
			return(tmp->value);
		tmp = tmp->next;
	}
}

static char *exchange_variable(char *str, t_env *env)
{
	int i;
	char *key;
	char *value;
	char *res;

	i = 0;
	res = (char *)malloc(sizeof(char) * 4096);
	if (!res)
		return (NULL);
	while (str && *str)
	{

		if (*str == '$')
		{
			key = get_key(&str);
			value = get_value(key, env);
			ft_strlcpy(res + i, value, ft_strlen(value) + 1);
			i += ft_strlen(value);
		}
		else
		{
			res[i] = *str;
			i++;
			str++;
		}
	}
	res[i] = '\0';
	return (res);
}

void handle_dollar_sign(char **cmd, t_env *env)
{
	int i;
	char *res;

	i = 0;
	while(cmd[i])
	{
		res = exchange_variable(cmd[i], env);
		cmd[i] = ft_strdup(res);
		i++;
	}
}

void parser(t_shell *shell)
{
	t_cmd *cmd;
	t_cmd *tmp;

	tmp = shell->cmd;
	while(tmp)
	{
		handle_dollar_sign(tmp->cmd, shell->env);
		tmp = tmp->next;
	}
}

int	main(int ac, char **av, char **env)
{
	t_shell		*shell;

	shell = init_shell(env);
	if (!shell)
		return (-1);
	while (1)
	{
		shell->line = readline("\033[1;31mRaRe\033[0m$ ");
		if (!shell->line)
		{
			// free(shell->line); // bakılacak
			continue ;
		}
		shell->tokens = tokenizer(shell->line, shell->env);
		if (!shell->tokens)
			continue ;
		shell->cmd = create_cmd(*(shell->tokens));
		parser(shell);
		handle_builtins(shell);

		if (!shell->cmd->is_builtin)
			execute_cmd(shell);

		// tcsetattr(STDIN_FILENO, TCSAFLUSH, &shell->terminal->minishell);
		// free(shell->line); // bakılacak
	}
	return (0);
}
