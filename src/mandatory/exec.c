/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:04:04 by emgul             #+#    #+#             */
/*   Updated: 2024/09/11 16:49:33 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include "readline/readline.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

static void	handle_cmd_errors(t_shell *shell, t_cmd *cmd)
{
	struct stat	statbuf;

	stat(cmd->arr[0], &statbuf);
	if (access(cmd->arr[0], X_OK) == -1 && access(cmd->arr[0], F_OK) == 0
		&& ft_strchr(cmd->arr[0], '/'))
		print_error(shell, cmd->arr[0], NULL, ERR_NOPERM, 0);
	else if (S_ISDIR(statbuf.st_mode) && ft_strchr(cmd->arr[0], '/'))
		print_error(shell, cmd->arr[0], NULL, ERR_ISDIR, 0);
	else if (access(cmd->arr[0], X_OK) == -1 || (access(cmd->arr[0], X_OK) == 0
			&& S_ISDIR(statbuf.st_mode)))
	{
		print_error(shell, cmd->arr[0], NULL, ERR_NOCMD, 0);
		ft_exit(shell, 127);
	}
	else if (access(cmd->arr[0], F_OK))
	{
		print_error(shell, cmd->arr[0], NULL, ERR_NODIR, 0);
		ft_exit(shell, 127);
	}
	ft_exit(shell, 126);
}

int	child_process(t_shell *shell, t_cmd *cmd)
{
	char	*path;

	path = find_valid_path(shell, cmd->arr[0], shell->env);
	if (!path)
		handle_cmd_errors(shell, cmd);
	if (!cmd->arr[0][0])
		ft_exit(shell, 0);
	execve(path, cmd->arr, shell->envp);
	ft_exit(shell, 1);
}

static bool	get_cond(int i, int j, int cmd_i, int cmdlen)
{
	if (cmd_i == 0)
		return (!(i == 0 && j == 1));
	else if (cmd_i == cmdlen - 1)
		return (!(i == cmdlen - 2 && j == 0));
	else
		return (!(i == cmd_i - 1 && j == 0) && !(i == cmd_i && j == 1));
}

void	close_fds(int fd[][2], int cmdlen, int cmd_i)
{
	int	i;
	int	j;

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

void	redirect_pipes(t_cmd *cmd, int fd[][2], int cmdlen, int i)
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

void	close_all_fds(int fd[][2], int cmdlen)
{
	int	i;

	i = 0;
	while (i < cmdlen - 1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

void	heredoc(t_cmd *cmd)
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

static void redir_heredoc(t_shell *shell, t_cmd *cmd)
{
	int	infd;
	
	heredoc(cmd);
	infd = open(HEREDOC_TMP_PATH, O_RDONLY, 0777);
	if (infd != -1)
	{
		dup2(infd, STDIN_FILENO);
		close(infd);
		unlink(HEREDOC_TMP_PATH);
	}
}

void	redirect_files(t_shell *shell, t_cmd *cmd)
{
	int	outfd;
	int	infd;

	outfd = open_outfile(shell, cmd);
	if (cmd->in_redir != HERE_DOC)
		infd = open_infile(shell, cmd);
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
		redir_heredoc(shell, cmd);
}

static void	wait_for_pids(t_shell *shell, pid_t *pid, int cmdlen)
{
	int	exit_status;
	int	i;

	i = 0;
	while (i < cmdlen)
	{
		waitpid(pid[i], &exit_status, 0);
		if (WIFEXITED(exit_status))
			*shell->last_exit_status = WEXITSTATUS(exit_status);
		i++;
	}
}

int	is_main_builtin(t_shell *shell, t_cmd *cmd)
{
	if (ft_strncmp(cmd->arr[0], "exit", higher_len(cmd->arr[0], "exit")) == 0)
		return (1);
	else if (ft_strncmp(cmd->arr[0], "cd", higher_len(cmd->arr[0], "cd")) == 0)
		return (1);
	else if (ft_strncmp(cmd->arr[0], "export", higher_len(cmd->arr[0],
				"export")) == 0)
		return (1);
	else if (ft_strncmp(cmd->arr[0], "unset", higher_len(cmd->arr[0],
				"unset")) == 0)
		return (1);
	else
		return (0);
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

void	handle_pipes(t_shell *shell, int fd[][2], int cmdlen, pid_t *pid)
{
	int		i;
	t_cmd	*cmd;

	cmd = shell->cmd;
	i = 0;
	while (i < cmdlen)
	{
		if (!cmd->arr[0])
			ft_exit(shell, 0);
		init_signal(SIGINT, NULL, &shell->sigint);
		if (cmdlen == 1)
			handle_builtins_main(shell, cmd);
		pid[i] = fork();
		if (pid[i] == 0)
			child(shell, cmd, fd, cmdlen, &i);
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
	handle_pipes(shell, fd, cmdlen, pid);
	init_signal(SIGINT, handle_sigint, &shell->sigint);
}
