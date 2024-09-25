/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:04:04 by emgul             #+#    #+#             */
/*   Updated: 2024/09/25 13:43:54 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <sys/stat.h>

char	*get_path(t_shell *shell, t_cmd *cmd)
{
	char		*path;
	struct stat	*statbuf;

	path = NULL;
	statbuf = ft_calloc(sizeof(struct stat), 1);
	stat(cmd->arr[0], statbuf);
	if (S_ISDIR(statbuf->st_mode))
	{
		free(statbuf);
		return (NULL);
	}
	else if (access(cmd->arr[0], X_OK) == 0)
		path = ft_strdup(cmd->arr[0]);
	else
		path = find_valid_path(cmd->arr[0], shell->env);
	free(statbuf);
	return (path);
}

static void	child(t_cmd *cmd, int fd[][2], int *i, char *path)
{
	int	cmdlen;

	cmdlen = cmd_len(cmd->shell->cmd);
	init_signal(SIGINT, child_signal_handler, &cmd->shell->sigint);
	init_signal(SIGQUIT, handle_sigquit, &cmd->shell->sigquit);
	redirect_pipes(fd, cmdlen, *i);
	redirect_files(cmd->shell, cmd);
	handle_builtins(cmd->shell, cmd);
	if (!cmd->is_builtin)
	{
		if (!cmd->arr[0][0])
			ft_exit(0);
		execve(path, cmd->arr, cmd->shell->envp);
		ft_exit(1);
	}
	ft_exit(0);
}

int	fork_child(t_cmd *cmd, int fd[][2], int *i)
{
	int		pid;
	char	*path;

	path = get_path(cmd->shell, cmd);
	if (!path && !is_builtin(cmd))
	{
		handle_cmd_errors(cmd->shell, cmd);
		(*i)++;
		return (1);
	}
	pid = fork();
	if (pid == 0)
		child(cmd, fd, i, path);
	free(path);
	return (0);
}

void	run_cmds(t_shell *shell, int fd[][2], int cmdlen)
{
	int		i;
	t_cmd	*cmd;

	cmd = shell->cmd;
	i = 0;
	while (i < cmdlen)
	{
		if (!cmd->arr[0])
			return ;
		init_signal(SIGINT, NULL, &shell->sigint);
		if (cmdlen == 1)
			handle_builtins_main(shell, cmd);
		if (!is_main_builtin(cmd))
		{
			if (fork_child(cmd, fd, &i))
				continue ;
		}
		i++;
		cmd = cmd->next;
	}
	close_all_fds(fd, cmdlen);
	wait_for_pids(shell);
}

void	execute_cmd(t_shell *shell)
{
	int		fd[ARG_MAX][2];
	int		cmdlen;
	int		i;

	cmdlen = cmd_len(shell->cmd);
	i = 0;
	while (i < cmdlen - 1)
	{
		if (pipe(fd[i]) == -1)
			return ;
		i++;
	}
	run_cmds(shell, fd, cmdlen);
	init_signal(SIGINT, handle_sigint, &shell->sigint);
}
