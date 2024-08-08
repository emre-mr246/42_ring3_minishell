/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:04:04 by emgul             #+#    #+#             */
/*   Updated: 2024/08/08 13:18:26 by emgul            ###   ########.fr       */
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

char	*make_path(char *uncompleted_path, char *cmd)
{
	char	*path_part;
	char	*valid_path;

	path_part = ft_strjoin(uncompleted_path, "/");
	if (!path_part)
		ft_exit(-1);
	valid_path = ft_strjoin(path_part, cmd);
	free(path_part);
	if (access(valid_path, F_OK) < 0)
		return (NULL);
	return (valid_path);
}

char	*find_valid_path(char *cmd, t_env *envp)
{
	int		i;
	char	**paths;
	char	*valid_path;
	t_env *env_tmp;

	env_tmp = envp;

	while (ft_strnstr(env_tmp->key, "PATH", 4) == 0)
		env_tmp = env_tmp->next;
	paths = ft_split(env_tmp->value, ':');
	if (!paths || !*paths)
		ft_exit(-1);
	i = 0;
	while (paths[i])
	{
		valid_path = make_path(paths[i++], cmd);
		if (valid_path != NULL)
			break ;
	}
	// free_array(paths);
	return (valid_path);
}

static void	child_signal_handler(int signum)
{
	if (signum == SIGINT)
		exit(130);
	else if (signum == SIGQUIT)
		exit(131);
}

int cmd_len(t_cmd *cmd)
{
	t_cmd *tmp;
	int len;

	tmp = cmd;
	len = 0;
	while(tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

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
        waitpid(pid[i], NULL, 0);
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
