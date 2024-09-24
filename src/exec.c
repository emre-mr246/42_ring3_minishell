/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:04:04 by emgul             #+#    #+#             */
/*   Updated: 2024/09/24 12:46:17 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>

char	*get_path(t_shell *shell, t_cmd *cmd)
{
	char	*path;
	struct stat	*statbuf;

	path = NULL;
	statbuf = ft_calloc(sizeof(struct stat), 1);
	stat(cmd->arr[0], statbuf);
	if (S_ISDIR(statbuf->st_mode))
	{
		free(statbuf);
		return (path);
	}
	else if (access(cmd->arr[0], X_OK) == 0)
		path = ft_strdup(cmd->arr[0]);
	else
		path = find_valid_path(cmd->arr[0], shell->env);
	free(statbuf);
	return (path);
}

int	child_process(t_shell *shell, t_cmd *cmd, char *path)
{
	if (!cmd->arr[0][0])
		ft_exit(0);
	execve(path, cmd->arr, shell->envp);
	ft_exit(1);
	return (1);
}

static void	wait_for_pids(t_shell *shell)
{
	int	exit_status;

	while (wait(&exit_status) > 0)
		continue ;
	if (WIFEXITED(exit_status))
	{
		*shell->exit_status = WEXITSTATUS(exit_status);
		//printf("Process exited normally with status: %d\n", *shell->exit_status);
	}
	// else if (WIFSIGNALED(exit_status)) {
	// 	int signal_num = WTERMSIG(exit_status);
	// 	printf("Process was terminated by signal: %d\n", signal_num);
	// 	if (WCOREDUMP(exit_status)) {
	// 		printf("Core dump occurred.\n");
	// 	}
	// }
	// else {
	// 	printf("Process did not exit normally.\n");
	// }
	// printf("exit stat: %i, ifexited: %i, wexit: %i\n", *shell->exit_status, WIFEXITED(exit_status), WEXITSTATUS(exit_status));
}

static void child(t_shell *shell, t_cmd *cmd, int fd[][2], int cmdlen, int *i, char *path)
{
	init_signal(SIGINT, child_signal_handler, &shell->sigint);
	init_signal(SIGQUIT, handle_sigquit, (void *)shell);
	redirect_pipes(fd, cmdlen, *i);
	redirect_files(shell, cmd);
	handle_builtins(shell, cmd);
	if (!cmd->is_builtin)
		child_process(shell, cmd, path);
	ft_exit(0);
}

void	run_cmds(t_shell *shell, int fd[][2], int cmdlen)
{
	int		i;
	t_cmd	*cmd;
	int		pid;
	char	*path;

	cmd = shell->cmd;
	path = NULL;
	i = 0;
	while (i < cmdlen)
	{
		if (!cmd->arr[0])
		{
			return ;
		}
		init_signal(SIGINT, NULL, &shell->sigint);
		if (cmdlen == 1)
		{
			handle_builtins_main(shell, cmd);
		}
		if (!is_main_builtin(cmd))
		{
			path = get_path(shell, cmd);
			if (!path)
			{
				handle_cmd_errors(shell, cmd);
				i++;
				continue ;
			}
			pid = fork();
			if (pid == 0)
			{
				child(shell, cmd, fd, cmdlen, &i, path);
			}
		}
		if (path)
			free(path);
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
