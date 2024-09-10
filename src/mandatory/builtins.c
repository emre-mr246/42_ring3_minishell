/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 21:41:54 by emgul             #+#    #+#             */
/*   Updated: 2024/09/10 22:58:04 by emgul            ###   ########.fr       */
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
#include <errno.h>

void ft_env(t_shell *shell, t_cmd *cmd)
{
	t_env *tmp;

	cmd->is_builtin = true;
	tmp = shell->env;
	while (tmp)
	{
		ft_putstr_fd(tmp->key, 1);
		ft_putstr_fd("=", 1);
		ft_putendl_fd(tmp->value, 1);
		tmp = tmp->next;
	}
}

void ft_echo(t_shell *shell, t_cmd *cmd)
{
	int i;
	bool newline;

	cmd->is_builtin = true;
	newline = true;
	i = 1;
	if(ft_strncmp(cmd->arr[1], "-n", higher_len(cmd->arr[1], "-n")) == 0)
	{
		i = 2;
		newline = false;
	}
	while (cmd->arr[i])
	{
		ft_putstr_fd(cmd->arr[i], 1);
		if (cmd->arr[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
}

void ft_cd(t_shell *shell, t_cmd *cmd)
{
	t_env *tmp;
	char *cwd;

	*(shell->last_exit_status) = 0;
	cmd->is_builtin = true;
	if (cmd->arr[2])
		print_error(shell, "too many args", "cd", -1, 0);
	tmp = shell->env;
	cwd = (char *)malloc(sizeof(char) * PATH_SIZE);
	if (!cwd)
		return ;
	getcwd(cwd, PATH_SIZE - 1);
	if (key_exists(tmp, "OLDPWD"))
		update_value(shell->env, "OLDPWD", cwd);
	else
		env_lstadd_back(&tmp, new_env("OLDPWD", cwd));
	if (chdir(cmd->arr[1]) == -1)
	{
		print_error(shell, cmd->arr[1], "cd", ERR_NODIR, 0);
		return ;
	}
	free(cwd);
	getcwd(cwd, PATH_SIZE - 1);
	update_value(shell->env, "PWD", cwd);
}

void handle_builtins(t_shell *shell, t_cmd *cmd)
{
	if (ft_strncmp(cmd->arr[0], "echo", higher_len(cmd->arr[0], "echo")) == 0)
        ft_echo(shell, cmd);
	else if (ft_strncmp(cmd->arr[0], "pwd", higher_len(cmd->arr[0], "pwd")) == 0)
	{
		cmd->is_builtin = true;
		ft_printf("%s\n", get_env_value(shell->env, "PWD"));
	}
	else if (ft_strncmp(cmd->arr[0], "env", higher_len(cmd->arr[0], "env")) == 0)
		ft_env(shell, cmd);
	else
		return ;
}

static int arg_numeric(t_shell *shell, char *arg)
{
	int i;

	i = 0;
	while (arg[i])
	{
		if ((i == 0 && arg[i] == '+')|| (i == 0 && arg[i] == '-') || arg[i] == '"' || arg[i] == '\'')
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

void handle_builtins_main(t_shell *shell, t_cmd *cmd)
{
	if(ft_strncmp(cmd->arr[0], "exit", higher_len(cmd->arr[0], "exit")) == 0)
	{
		if (!cmd->arr[1])
			ft_exit(*shell->last_exit_status);
		else if (!arg_numeric(shell, cmd->arr[1]))
			print_error(shell, NULL, "exit", ERR_NONNUM, 0);
		else if (cmd->arr[2])
			print_error(shell, "too many args", "exit", -1, 0);
		else if (cmd->arr[1])
			*shell->last_exit_status = ft_atoi(cmd->arr[1]);
		ft_exit(*shell->last_exit_status);
	}
	else if(ft_strncmp(cmd->arr[0], "cd", higher_len(cmd->arr[0], "cd")) == 0)
		ft_cd(shell, cmd);
	else if(ft_strncmp(cmd->arr[0], "export", higher_len(cmd->arr[0], "export")) == 0)
		ft_export(shell, cmd);
	else if(ft_strncmp(cmd->arr[0], "unset", higher_len(cmd->arr[0], "unset")) == 0)
		ft_unset(shell, cmd);
	else
		return ;
}