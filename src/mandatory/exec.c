/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:04:04 by emgul             #+#    #+#             */
/*   Updated: 2024/08/09 12:06:58 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../lib/libft/libft.h"
#include "readline/history.h"
#include "readline/readline.h"
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <limits.h>
#include <linux/limits.h>

void child_process(t_shell *shell, t_cmd *cmd)
{
	char *path;
	int result;

	init_signal(SIGINT, child_signal_handler, &shell->sigint);
	init_signal(SIGQUIT, handle_sigquit, &shell->sigquit);
	path = find_valid_path(cmd->arr[0], shell->env);
	result = execve(path, cmd->arr, shell->envp);
	if (result == -1)
		ft_putendl_fd("HATA", 2);
	exit(0);
}

static bool get_cond(int i, int j, int cmd_i, int cmdlen)
{
	if (cmd_i == 0)
		return (!(i == 0 && j == 1));
	else if (cmd_i == cmdlen - 1)
		return (!(i == cmdlen - 2 && j == 0));
	else
		return (!(i == cmd_i - 1 && j == 0) && !(i == cmd_i && j == 1));
}

void close_fds(int fd[][2], int cmdlen, int cmd_i)
{
	int i;
	int j;

	i = 0;
	while (i < cmdlen - 1)
	{
		j = 0;
		while (j < 2)
		{
			if (get_cond(i, j, cmd_i, cmdlen))
				close(fd[i][j]);
			j++;
		}
		i++;
	}
}

void redirect_pipes(t_cmd *cmd, int fd[][2], int cmdlen, int i)
{
	close_fds(fd, cmdlen, i);
	if (i != cmdlen - 1)
	{
		dup2(fd[i][1], STDOUT_FILENO);
		close(fd[i][1]);
	}
	if (i != 0)
	{
		dup2(fd[i - 1][0], STDIN_FILENO);
		close(fd[i - 1][0]);				
	}
}

void close_all_fds(int fd[][2], int cmdlen)
{
	int i;
	
	i = 0;
	while (i < cmdlen - 1)
    {
        close(fd[i][0]);
        close(fd[i][1]);
		i++;
    }
}

void handle_pipes(t_shell *shell, int fd[][2], int cmdlen, pid_t *pid)
{
	int	i;
	t_cmd	*cmd;
	
	cmd = shell->cmd;
	i = 0;
	while (i < cmdlen)
	{
		pid[i] = fork();
		if (pid[i] == 0)
		{
			redirect_pipes(cmd, fd, cmdlen, i);
			handle_builtins(shell);
			if (!cmd->is_builtin)
				child_process(shell, cmd);
			cmd->is_builtin = false;
		}
		i++;
		cmd = cmd->next;
	}		
	close_all_fds(fd, cmdlen);				
	i = -1;
	while (++i < cmdlen)
        waitpid(pid[i], shell->last_exit_status, 0);
}
void execute_cmd(t_shell *shell)
{
	int fd[100][2];
	int cmdlen;
	int i;
	t_cmd	*cmd;
	pid_t *pid;

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
	handle_pipes(shell, fd, cmdlen, pid);
}
