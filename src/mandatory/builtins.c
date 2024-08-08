/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 21:41:54 by emgul             #+#    #+#             */
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
	if(ft_strncmp(shell->cmd->arr[1], "-n", get_higher_len(shell->cmd->arr[1], "-n")) == 0)
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

void handle_builtins(t_shell *shell)
{
	if(ft_strncmp(shell->cmd->arr[0], "exit", get_higher_len(shell->cmd->arr[0], "exit")) == 0)
        ft_exit(EXIT_SUCCESS);
	if(ft_strncmp(shell->cmd->arr[0], "echo", get_higher_len(shell->cmd->arr[0], "echo")) == 0)
        ft_echo(shell);
	if(ft_strncmp(shell->cmd->arr[0], "cd", get_higher_len(shell->cmd->arr[0], "cd")) == 0)
		ft_cd(shell);
	if(ft_strncmp(shell->cmd->arr[0], "pwd", get_higher_len(shell->cmd->arr[0], "pwd")) == 0)
	{
		shell->cmd->is_builtin = true;
		ft_printf("%s\n", get_env_value(shell->env, "PWD"));
	}
	if(ft_strncmp(shell->cmd->arr[0], "export", get_higher_len(shell->cmd->arr[0], "export")) == 0)
		ft_export(shell);
	if(ft_strncmp(shell->cmd->arr[0], "unset", get_higher_len(shell->cmd->arr[0], "unset")) == 0)
		ft_unset(shell);
	if(ft_strncmp(shell->cmd->arr[0], "env", get_higher_len(shell->cmd->arr[0], "env")) == 0)
		ft_env(shell);
}
