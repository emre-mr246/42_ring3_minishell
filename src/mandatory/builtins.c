/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 21:41:54 by emgul             #+#    #+#             */
/*   Updated: 2024/09/16 15:32:17 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <readline/history.h>
#include <readline/readline.h>

void	ft_env(t_shell *shell, t_cmd *cmd)
{
	t_env	*tmp;

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

void	ft_echo(t_shell *shell, t_cmd *cmd)
{
	int		i;
	bool	newline;

	cmd->is_builtin = true;
	newline = true;
	i = 1;
	if (ft_strncmp(cmd->arr[1], "-n", higher_len(cmd->arr[1], "-n")) == 0)
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

void	ft_cd(t_shell *shell, t_cmd *cmd)
{
	t_env	*tmp;
	char	*cwd;

	*(shell->last_exit_status) = 0;
	cmd->is_builtin = true;
	if (cmd->arr[2])
		print_error(shell, "too many args", "cd", ERR_MANYARGS, 0);
	tmp = shell->env;
	cwd = (char *)ft_calloc(sizeof(char), PATH_SIZE);
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

void	handle_builtins(t_shell *shell, t_cmd *cmd)
{
	if (ft_strncmp(cmd->arr[0], "echo", higher_len(cmd->arr[0], "echo")) == 0)
		ft_echo(shell, cmd);
	else if (ft_strncmp(cmd->arr[0], "pwd", higher_len(cmd->arr[0],
				"pwd")) == 0)
	{
		cmd->is_builtin = true;
		ft_printf("%s\n", get_env_value(shell->env, "PWD"));
	}
	else if (ft_strncmp(cmd->arr[0], "env", higher_len(cmd->arr[0],
				"env")) == 0)
		ft_env(shell, cmd);
	else
		return ;
}

void	ft_exit(t_shell *shell, int exit_code)
{
	rl_clear_history();
	free_all(shell);
	exit(exit_code);
}
