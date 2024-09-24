/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:27:51 by emgul             #+#    #+#             */
/*   Updated: 2024/09/24 14:10:49 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

static int	env_search_export(t_shell *shell, int j)
{
	int	i;

	i = 0;
	while (shell->cmd->arr[j][i])
	{
		if (shell->cmd->arr[j][i] == '=')
			break ;
		i++;
	}
	if (i == 0)
		print_error(shell, shell->cmd->arr[j], ERR_ENVNAME, 0);
	return (i);
}

void	key_valid(t_shell *shell, char *key)
{
	int	i;

	if (ft_isdigit(key[0]))
		print_error(shell, key, ERR_ENVNAME, 0);
	i = 0;
	while (key[i])
	{
		if (!(ft_isalnum(key[i]) || key[i] == '_'))
			print_error(shell, key, ERR_ENVNAME, 0);
		i++;
	}
}

static char	*get_export_key(t_shell *shell, int *j)
{
	int		i;
	char	*key;

	i = env_search_export(shell, *j);
	if (i == 0)
		return (NULL);
	key = ft_substr(shell->cmd->arr[*j], 0, i);
	key_valid(shell, key);
	return (key);
}

void	ft_export(t_shell *shell, t_cmd *cmd)
{
	int		i;
	int		j;
	char	*key;
	char	*value;

	cmd->is_builtin = true;
	j = 1;
	while (cmd->arr[j])
	{
		key = get_export_key(shell, &j);
		if (!key)
			return ;
		i = env_search_export(shell, j);
		value = ft_substr(cmd->arr[j], i + 1, ft_strlen(cmd->arr[j]) - (i + 1));
		if (key_exists(shell->env, key))
			update_value(shell->env, key, value);
		else
			env_lstadd_back(&shell->env, new_env(key, value));
		j++;
		free(key);
		if (value)
			free(value);
	}
}

int	is_main_builtin(t_cmd *cmd)
{
	if (ft_strncmp(cmd->arr[0], "exit", higher_len(cmd->arr[0], "exit")) == 0)
		return (1);
	else if (ft_strncmp(cmd->arr[0], "cd", higher_len(cmd->arr[0], "cd")) == 0)
		return (1);
	else if (ft_strncmp(cmd->arr[0], "export", higher_len(cmd->arr[0],
				"export")) == 0)
		return (1);
	else if (ft_strncmp(cmd->arr[0], "unset", higher_len(cmd->arr[0],
				"unset")) == 0)
		return (1);
	else
		return (0);
}
