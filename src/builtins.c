/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 21:41:54 by emgul             #+#    #+#             */
/*   Updated: 2024/09/24 14:11:34 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include "readline/readline.h"
#include "readline/history.h"

static void	ft_env(t_shell *shell, t_cmd *cmd)
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

static void	ft_echo(t_cmd *cmd)
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

static void	write_oldpwd(t_shell *shell, char *cwd)
{
	t_env	*env;

	env = shell->env;
	if (key_exists(env, "OLDPWD"))
		update_value(shell->env, "OLDPWD", cwd);
	else
		env_lstadd_back(&env, new_env("OLDPWD", cwd));
}

void	ft_cd(t_shell *shell, t_cmd *cmd)
{
	char	*cwd;
	char	*path;

	cmd->is_builtin = true;
	cwd = (char *)ft_calloc(sizeof(char), PATH_SIZE);
	if (!cwd)
		return ;
	getcwd(cwd, PATH_SIZE - 1);
	write_oldpwd(shell, cwd);
	if (cmd->arr[1])
		path = ft_strdup(cmd->arr[1]);
	else
		path = get_env_value(shell->env, "HOME");
	if (path && chdir(path) == -1)
	{
		print_error(shell, path, ERR_NODIR, 0);
		free(cwd);
		free(path);
		return ;
	}
	getcwd(cwd, PATH_SIZE - 1);
	update_value(shell->env, "PWD", cwd);
	free(path);
	free(cwd);
}

void	handle_builtins(t_shell *shell, t_cmd *cmd)
{
	char	*val;

	if (ft_strncmp(cmd->arr[0], "echo", higher_len(cmd->arr[0], "echo")) == 0)
		ft_echo(cmd);
	else if (ft_strncmp(cmd->arr[0], "pwd", higher_len(cmd->arr[0],
				"pwd")) == 0)
	{
		cmd->is_builtin = true;
		val = get_env_value(shell->env, "PWD");
		ft_printf("%s\n", val);
		free(val);
	}
	else if (ft_strncmp(cmd->arr[0], "env", higher_len(cmd->arr[0],
				"env")) == 0)
		ft_env(shell, cmd);
	else
		return ;
}
