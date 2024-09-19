/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:04:04 by emgul             #+#    #+#             */
/*   Updated: 2024/09/19 19:18:46 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

int	child_process(t_shell *shell, t_cmd *cmd)
{
	char	*path;

	path = find_valid_path(shell, cmd->arr[0], shell->env);
	if (!path)
		handle_cmd_errors(shell, cmd);
	if (!cmd->arr[0][0])
		ft_exit(shell, 0);
	execve(path, cmd->arr, shell->envp);
	free(path);
	ft_exit(shell, 1);
	return (1);
}

static void	wait_for_pids(t_shell *shell)
{
	int	exit_status;

	while (wait(&exit_status) > 0)
		continue ;
	if (WIFEXITED(exit_status))
		*shell->exit_status = WEXITSTATUS(exit_status);
}

static void child(t_shell *shell, t_cmd *cmd, int fd[][2], int cmdlen, int *i)
{
	init_signal(SIGINT, child_signal_handler, &shell->sigint);
	init_signal(SIGQUIT, handle_sigquit, (void *)shell);
	redirect_pipes(cmd, fd, cmdlen, *i);
	redirect_files(shell, cmd);
	if (is_main_builtin(shell, cmd))
		ft_exit(shell, *shell->exit_status);
	handle_builtins(shell, cmd);
	if (!cmd->is_builtin)
		child_process(shell, cmd);
	ft_exit(shell, 0);
}

void	run_cmds(t_shell *shell, int fd[][2], int cmdlen)
{
	int		i;
	t_cmd	*cmd;
	int		pid;

	cmd = shell->cmd;
	i = 0;
	while (i < cmdlen)
	{
		if (!cmd->arr[0])
		{
			ft_exit(shell, 0);
		}
		init_signal(SIGINT, NULL, &shell->sigint);
		if (cmdlen == 1)
		{
			handle_builtins_main(shell, cmd);
		}
		pid = fork();
		if (pid == 0)
		{
			child(shell, cmd, fd, cmdlen, &i);
		}
		i++;
		cmd = cmd->next;
	}
	close_all_fds(fd, cmdlen);
	wait_for_pids(shell);
}

void	execute_cmd(t_shell *shell)
{
	int		fd[100][2];
	int		cmdlen;
	int		i;
	t_cmd	*cmd;

	cmdlen = cmd_len(shell->cmd);
	cmd = shell->cmd;
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
