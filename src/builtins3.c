/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:00:05 by mitasci           #+#    #+#             */
/*   Updated: 2024/09/24 12:52:44 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static t_env	*get_prev_node(t_env *env, char *key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp->next)
	{
		if (ft_strncmp(tmp->next->key, key, higher_len(tmp->next->key,
					key)) == 0)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

static void	ft_unset_key(t_shell *shell, char *key)
{
	t_env	*node;
	t_env	*prev_node;
	t_env	*next_node;

	next_node = NULL;
	prev_node = NULL;
	node = NULL;
	if (ft_strncmp(shell->env->key, key, higher_len(shell->env->key, key) == 0))
	{
		next_node = shell->env->next;
		free_env(shell->env);
		shell->env = next_node;
		return ;
	}
	prev_node = get_prev_node(shell->env, key);
	node = prev_node->next;
	if (!node)
		return ;
	next_node = node->next;
	free_env(node);
	prev_node->next = next_node;
}

void	ft_unset(t_shell *shell, t_cmd *cmd)
{
	int	i;

	i = 1;
	cmd->is_builtin = true;
	while (cmd->arr[i])
	{
		key_valid(shell, cmd->arr[i]);
		ft_unset_key(shell, cmd->arr[i]);
		i++;
	}
}

static int	arg_numeric(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if ((i == 0 && arg[i] == '+') || (i == 0 && arg[i] == '-')
			|| arg[i] == '"' || arg[i] == '\'')
		{
			i++;
			continue ;
		}
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}
void	print_exit_error(t_shell *shell, t_cmd *cmd)
{
	if (!arg_numeric(cmd->arr[1]))
			print_error(shell, NULL, ERR_NONNUM, 0);
	else if (cmd->arr[2])
		print_error(shell, "too many args", ERR_MANYARGS, 0);
	else if (cmd->arr[1])
		*shell->exit_status = ft_atoi(cmd->arr[1]);
}

void	handle_builtins_main(t_shell *shell, t_cmd *cmd)
{
	int	exstat;
	
	if (ft_strncmp(cmd->arr[0], "exit", higher_len(cmd->arr[0], "exit")) == 0)
	{
		exstat = *shell->exit_status;
		if (!cmd->arr[1])
		{
			free_all(shell);
			ft_exit(exstat);
		}
		print_exit_error(shell, cmd);
		exstat = *shell->exit_status;
		free_all(shell);
		ft_exit(exstat);
	}
	else if (ft_strncmp(cmd->arr[0], "cd", higher_len(cmd->arr[0], "cd")) == 0)
		ft_cd(shell, cmd);
	else if (ft_strncmp(cmd->arr[0], "export", higher_len(cmd->arr[0],
				"export")) == 0)
		ft_export(shell, cmd);
	else if (ft_strncmp(cmd->arr[0], "unset", higher_len(cmd->arr[0],
				"unset")) == 0)
		ft_unset(shell, cmd);
	else
		return ;
}
