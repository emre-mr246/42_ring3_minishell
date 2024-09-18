/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 21:27:42 by emgul             #+#    #+#             */
/*   Updated: 2024/09/18 21:36:32 by emgul            ###   ########.fr       */
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

void	free_all(t_shell *shell)
{
	t_env *tmp_env;

	while (shell->env)
	{
		tmp_env = shell->env;
		shell->env = shell->env->next;
		free(tmp_env->key);
		free(tmp_env->value);
		free(tmp_env);
	}
	if (shell->last_exit_status)
		free(shell->last_exit_status);
	if (shell)
		free(shell);
}