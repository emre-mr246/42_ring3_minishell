/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:04:04 by emgul             #+#    #+#             */
/*   Updated: 2024/09/17 16:57:42 by mitasci          ###   ########.fr       */
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

static void	wait_for_pids(t_shell *shell, pid_t *pid, int cmdlen)
{
	int	exit_status;
	int	i;
	// int pid_tmp[42];

	// i = 0;
	// while (pid[i])
	// 	pid_tmp[i] = pid[i];
	// free(pid);
	i = 0;
	while (i < cmdlen)
	{
		waitpid(pid[i], &exit_status, 0); //pid_tmp[i]
		if (WIFEXITED(exit_status))
			*shell->last_exit_status = WEXITSTATUS(exit_status);
		i++;
	}
}

static void child(t_shell *shell, t_cmd *cmd, int fd[][2], int cmdlen, int *i)
{
	init_signal(SIGINT, child_signal_handler, &shell->sigint);
	init_signal(SIGQUIT, handle_sigquit, (void *)shell);
	redirect_pipes(cmd, fd, cmdlen, *i);
	redirect_files(shell, cmd);
	if (is_main_builtin(shell, cmd))
		ft_exit(shell, *shell->last_exit_status);
	handle_builtins(shell, cmd);
	if (!cmd->is_builtin)
		child_process(shell, cmd);
	ft_exit(shell, 0);
}

void	run_cmds(t_shell *shell, int fd[][2], int cmdlen, pid_t *pid)
{
	int		i;
	t_cmd	*cmd;

	cmd = shell->cmd;
	i = 0;
	while (i < cmdlen)
	{
		if (!cmd->arr[0])
		{
			free(pid);
			ft_exit(shell, 0);
		}
		init_signal(SIGINT, NULL, &shell->sigint);
		if (cmdlen == 1)
		{
			if (ft_strncmp(cmd->arr[0], "exit", higher_len(cmd->arr[0], "exit")) == 0)
				free(pid);
			handle_builtins_main(shell, cmd);
		}
		pid[i] = fork();
		if (pid[i] == 0)
		{
			free(pid);
			child(shell, cmd, fd, cmdlen, &i);
		}
		i++;
		cmd = cmd->next;
	}
	close_all_fds(fd, cmdlen);
	wait_for_pids(shell, pid, cmdlen);
}

void	execute_cmd(t_shell *shell)
{
	int		fd[100][2];
	int		cmdlen;
	int		i;
	t_cmd	*cmd;
	pid_t	*pid;

	cmdlen = cmd_len(shell->cmd);
	pid = (pid_t *)ft_calloc(sizeof(pid_t), cmdlen);
	if (!pid)
		return ;
	cmd = shell->cmd;
	i = 0;
	while (i < cmdlen - 1)
	{
		if (pipe(fd[i]) == -1)
		{
			free(pid);
			return ;
		}
		i++;
	}
	run_cmds(shell, fd, cmdlen, pid);
	if (pid)
		free(pid);
	init_signal(SIGINT, handle_sigint, &shell->sigint);
}
