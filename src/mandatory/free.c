/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 21:27:42 by emgul             #+#    #+#             */
/*   Updated: 2024/09/19 15:55:28 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	if (arr)
		free(arr);
}

void	free_cmds(t_shell *shell)
{
	t_cmd	*tmp_cmd;

	while (shell->cmd)
	{
		tmp_cmd = shell->cmd;
		free_array(tmp_cmd->arr);
		if (tmp_cmd->infile)
			free(tmp_cmd->infile);
		if (tmp_cmd->outfile)
			free(tmp_cmd->outfile);
		shell->cmd = shell->cmd->next;
		free(tmp_cmd);
	}
}

void	free_env(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
}

void	free_envs(t_shell *shell)
{
	t_env *tmp_env;
	
	while (shell->env)
	{
		tmp_env = shell->env;
		shell->env = shell->env->next;
		free_env(tmp_env);
	}
}

void	free_all(t_shell *shell)
{
	if (shell->cmd)
		free_cmds(shell);
	if (shell->env)
		free_envs(shell);
	if (shell)
		free(shell);
}