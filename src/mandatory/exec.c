/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:04:04 by emgul             #+#    #+#             */
/*   Updated: 2024/08/22 23:08:44 by emgul            ###   ########.fr       */
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

int child_process(t_shell *shell, t_cmd *cmd)
{
	char *path;
	int result;

	path = find_valid_path(cmd->arr[0], shell->env);
	result = execve(path, cmd->arr, shell->envp);
	if (result == -1)
		perror("execve");
	exit(1);
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

void heredoc(t_cmd *cmd)
{
	char	*line;
	char	*delim;
	int		tmpfd;

	tmpfd = open(HEREDOC_TMP_PATH, O_CREAT | O_RDWR, 0777);
	delim = ft_strdup(cmd->infile);
	line = NULL;
	while (1)
	{
		line = readline(">");
		if (!line)
			return ;
		if (ft_strncmp(line, delim, higher_len(line, delim)) == 0)
			break ;
		ft_putendl_fd(line, tmpfd);
		free(line);
	}
	free(line);
	close(tmpfd);
}

void redirect_files(t_cmd *cmd)
{
	int outfd;
	int	infd;

	outfd = open_outfile(cmd);
	if (cmd->in_redir != HERE_DOC)
		infd = open_infile(cmd);
	else
		infd = -1;
	if (outfd != -1 && (cmd->out_redir == REDIRECT_OUTPUT || cmd->out_redir == APPEND_OUTPUT))
	{
		dup2(outfd, STDOUT_FILENO);
		close(outfd);
	}
	if (infd != -1 && cmd->in_redir == REDIRECT_INPUT)
	{
		dup2(infd, STDIN_FILENO);
		close(infd);
	}
	if (cmd->in_redir == HERE_DOC)
	{
		heredoc(cmd);
		infd = open(HEREDOC_TMP_PATH, O_RDONLY, 0777);
		if (infd != -1)
		{
			dup2(infd, STDIN_FILENO);
			close(infd);
			unlink(HEREDOC_TMP_PATH);
		}
	}
}

static void wait_for_pids(t_shell *shell, pid_t *pid, int cmdlen)
{
	int exit_status;
	int failed;
	int i;

	failed = 0;	
	waitpid(pid[0], &exit_status, 0);
    if (WIFEXITED(exit_status) && WEXITSTATUS(exit_status) != 0)
    {
        *shell->last_exit_status = WEXITSTATUS(exit_status);
        failed = 1;
    }
	i = 1;
    while (i < cmdlen)
    {
        if (failed)
            kill(pid[i], SIGKILL);
        waitpid(pid[i], &exit_status, 0);
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
		init_signal(SIGINT, NULL, &shell->sigint);
		pid[i] = fork();
		if (pid[i] == 0)
		{
			init_signal(SIGINT, child_signal_handler, &shell->sigint);
			init_signal(SIGQUIT, handle_sigquit, &shell->sigquit);
			redirect_pipes(cmd, fd, cmdlen, i);
			redirect_files(cmd);
			handle_builtins(shell, cmd);
			handle_builtins_main(shell, cmd);
			if (!cmd->is_builtin)
				child_process(shell, cmd);
			exit(0);
		}
		i++;
		cmd = cmd->next;
	}
	close_all_fds(fd, cmdlen);	
	wait_for_pids(shell, pid, cmdlen);
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
	init_signal(SIGINT, handle_sigint, &shell->sigint);
}
