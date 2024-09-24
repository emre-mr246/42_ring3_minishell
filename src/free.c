/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 12:29:50 by emgul             #+#    #+#             */
/*   Updated: 2024/09/24 12:58:27 by mitasci          ###   ########.fr       */
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
	t_cmd		*tmp_cmd;
	t_cmd		*next_cmd;

	while (shell->cmd)
	{
		tmp_cmd = shell->cmd;
		if (tmp_cmd->arr)
			free_array(tmp_cmd->arr);
		if (tmp_cmd->heredoc_arr)
			free_array(tmp_cmd->heredoc_arr);
		if (tmp_cmd->infile)
			free(tmp_cmd->infile);
		if (tmp_cmd->outfile)
			free(tmp_cmd->outfile);
		next_cmd = shell->cmd->next;
		free(tmp_cmd);
		shell->cmd = next_cmd;
	}
}

void	free_env(t_env *env)
{
	free(env->key);
	free(env->value);
	free(env);
}

void	free_all(t_shell *shell)
{
	t_env		*tmp_env;

	while (shell->env)
	{
		tmp_env = shell->env;
		shell->env = shell->env->next;
		free_env(tmp_env);
	}
	if (shell->cmd)
		free_cmds(shell);
	if (shell->exit_status)
		free(shell->exit_status);
	if (shell)
		free(shell);
}
