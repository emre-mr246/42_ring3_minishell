/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:27:51 by emgul             #+#    #+#             */
/*   Updated: 2024/08/08 13:37:34 by emgul            ###   ########.fr       */
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

static int env_search_export(t_shell *shell, int j)
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
		i = env_search_export(shell, j);
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

static t_env *get_prev_node(t_env *env, char *key)
{
	t_env *tmp;
	int i = 0;

	tmp = env;
	while (tmp->next)
	{
		if (ft_strncmp(tmp->next->key, key, get_higher_len(tmp->next->key, key)) == 0)
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
	if (ft_strncmp(shell->env->key, key, get_higher_len(shell->env->key, key) == 0))
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