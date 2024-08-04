/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 21:41:54 by emgul             #+#    #+#             */
/*   Updated: 2024/08/04 23:48:40 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../lib/libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

static int env_search(t_shell *shell, int j)
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

void ft_echo(t_shell *shell)
{
	int i;
	bool newline;

	shell->cmd->is_builtin = true;
	newline = true;
	i = 1;
	if(ft_strncmp(shell->cmd->arr[1], "-n", max_len(shell->cmd->arr[1], "-n")) == 0)
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

t_env *get_prev_node(t_env *env, char *key)
{
	t_env *tmp;
	int i = 0;

	tmp = env;
	while (tmp->next)
	{
		if (ft_strncmp(tmp->next->key, key, max_len(tmp->next->key, key)) == 0)
			break ;
		tmp = tmp->next;
		i++;
	}
	return (tmp);
}

static void ft_unset_key(t_shell *shell, char *key)
{
	t_env *node;
	t_env *prev_node;
	t_env *next_node;
	
	next_node = NULL;
	prev_node = NULL;
	node = NULL;
	if (ft_strncmp(shell->env->key, key, max_len(shell->env->key, key) == 0))
	{
		next_node = shell->env->next;
		free(shell->env->key);
		free(shell->env->value);
		free(shell->env);
		shell->env = next_node;
		return ;
	}
	prev_node = get_prev_node(shell->env, key);
	node = prev_node->next;
	if (!node)
		return ;
	next_node = node->next;
	free(node->key);
	free(node->value);
	free(node);
	prev_node->next = next_node;
}

void ft_unset(t_shell *shell)
{
	int i;

	i = 1;
	shell->cmd->is_builtin = true;
	while (shell->cmd->arr[i])
	{
		ft_unset_key(shell, shell->cmd->arr[i]);
		i++;
	}
}

void handle_builtins(t_shell *shell)
{
	if(ft_strncmp(shell->cmd->arr[0], "exit", max_len(shell->cmd->arr[0], "exit")) == 0)
        exit(EXIT_SUCCESS);
	if(ft_strncmp(shell->cmd->arr[0], "echo", max_len(shell->cmd->arr[0], "echo")) == 0)
        ft_echo(shell);
	if(ft_strncmp(shell->cmd->arr[0], "cd", max_len(shell->cmd->arr[0], "cd")) == 0)
		ft_cd(shell);
	if(ft_strncmp(shell->cmd->arr[0], "pwd", max_len(shell->cmd->arr[0], "pwd")) == 0)
	{
		shell->cmd->is_builtin = true;
		ft_printf("%s\n", get_env_value(shell->env, "PWD"));
	}
	if(ft_strncmp(shell->cmd->arr[0], "export", max_len(shell->cmd->arr[0], "export")) == 0)
		ft_export(shell);
	if(ft_strncmp(shell->cmd->arr[0], "unset", max_len(shell->cmd->arr[0], "unset")) == 0)
		ft_unset(shell);
	if(ft_strncmp(shell->cmd->arr[0], "env", max_len(shell->cmd->arr[0], "env")) == 0)
		ft_env(shell);
}
