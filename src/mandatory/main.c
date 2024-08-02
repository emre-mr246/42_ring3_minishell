/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:48:40 by emgul             #+#    #+#             */
/*   Updated: 2024/08/02 13:52:55 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../lib/libft/libft.h"
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

	shell->cmd->is_builtin = true;
	newline = true;
	i = 1;
	if(ft_strncmp(shell->cmd->arr[1], "-n", ft_strlen(shell->cmd->arr[1])) == 0)
	{
		i = 2;
		newline = false;
	}
	while (shell->cmd->arr[i])
	{
		ft_putstr_fd(shell->cmd->arr[i], 1);
		write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
}

char *print_env(t_env *env, char *key)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(tmp->key)) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (tmp->value);
}

void print_cmd(t_shell *shell)
{
	t_cmd *cmd;
	int i;
	
	cmd = shell->cmd;
	i = 0;
	while (cmd->arr[i])
	{
		printf("CMD: %s\n", cmd->arr[i]);
		i++;
	}
}

void ft_cd(t_shell *shell)
{
	t_env *tmp;
	char *cwd;

	shell->cmd->is_builtin = true;
	tmp = shell->env;
	cwd = (char *)malloc(sizeof(char) * PATH_SIZE);
	if (!cwd)
		return ;
	getcwd(cwd, PATH_SIZE - 1);
	if (key_exists(tmp, "OLDPWD"))
		update_value(shell->env, "OLDPWD", cwd);
	else
		env_lstadd_back(&tmp, new_env("OLDPWD", cwd));
	chdir(shell->cmd->arr[1]);
	free(cwd);
	getcwd(cwd, PATH_SIZE - 1);
	update_value(shell->env, "PWD", cwd);
}

void ft_env(t_shell *shell)
{
	t_env *tmp;

	shell->cmd->is_builtin = true;
	tmp = shell->env;
	while (tmp)
	{
		ft_putstr_fd(tmp->key, 1);
		ft_putstr_fd("=", 1);
		ft_putendl_fd(tmp->value, 1);
		tmp = tmp->next;
	}
}

int env_search(t_shell *shell, int j)
{
	int i;

	i = 0;
	while (shell->cmd->arr[j][i])
	{
		if (shell->cmd->arr[j][i] == '=')
			break ;
		i++;
	}
	if (i == 0)
	{
		ft_printf("-RaRe: export: '%s': not a valid identifier\n", shell->cmd->arr[j]);
		return (-1);
	}
	return (i);
}

void ft_export(t_shell *shell)
{
	int i;
	int j;
	char *key;
	char *value;

	shell->cmd->is_builtin = true;
	j = 1;
	while(shell->cmd->arr[j])
	{
		i = env_search(shell, j);
		if (i == -1)
			return ;
		if (shell->cmd->arr[j][i] != '=')
		{
			j++;
			continue ;
		}
		key = ft_substr(shell->cmd->arr[j], 0, i);
		value = ft_substr(shell->cmd->arr[j], i + 1, ft_strlen(shell->cmd->arr[j]) - (i + 1));
		if (key_exists(shell->env, key))
			update_value(shell->env, key, value);
		else
			env_lstadd_back(&shell->env, new_env(key, value));
		j++;
	}
}

void handle_builtins(t_shell *shell)
{
	if(ft_strncmp(shell->cmd->arr[0], "exit", ft_strlen(shell->cmd->arr[0])) == 0)
        exit(EXIT_SUCCESS);
	if(ft_strncmp(shell->cmd->arr[0], "echo", ft_strlen(shell->cmd->arr[0])) == 0)
        ft_echo(shell);
	if(ft_strncmp(shell->cmd->arr[0], "cd", ft_strlen(shell->cmd->arr[0])) == 0)
		ft_cd(shell);
	if(ft_strncmp(shell->cmd->arr[0], "pwd", ft_strlen(shell->cmd->arr[0])) == 0)
	{
		shell->cmd->is_builtin = true;
		ft_printf("%s\n", print_env(shell->env, "PWD"));
	}
	if(ft_strncmp(shell->cmd->arr[0], "export", ft_strlen(shell->cmd->arr[0])) == 0)
		ft_export(shell);
	if(ft_strncmp(shell->cmd->arr[0], "unset", ft_strlen(shell->cmd->arr[0])) == 0)
		exit(EXIT_SUCCESS);
	if(ft_strncmp(shell->cmd->arr[0], "env", ft_strlen(shell->cmd->arr[0])) == 0)
		ft_env(shell);
}

char *create_prompt(t_shell *shell)
{
	char	*prompt;
	char	*tmp;

	prompt = ft_strjoin("\033[1;31mRaRe\033[0m$:\033[1;34m", print_env(shell->env, "PWD"));
	tmp = prompt;
	prompt = ft_strjoin(tmp, "\033[0m$ ");
	free(tmp);
	return (prompt);
}

int	main(int ac, char **av, char **env)
{
	t_shell		*shell;

	shell = init_shell(env);
	if (!shell)
		return (-1);
	while (1)
	{
		shell->line = readline(create_prompt(shell));
		if (!shell->line)
		{
			// free(shell->line); // bakılacak
			continue ;
		}
		shell->tokens = tokenizer(shell->line, shell->env);
		if (!shell->tokens)
			continue ;
		shell->cmd = create_cmd(*(shell->tokens));
		print_cmd(shell);

		parser(shell);
		handle_builtins(shell);

		if (!shell->cmd->is_builtin)
			execute_cmd(shell);
		shell->cmd->is_builtin = false;

		free(shell->line); // bakılacak
	}
	return (0);
}
