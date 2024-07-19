/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 18:04:04 by emgul             #+#    #+#             */
/*   Updated: 2024/07/19 18:12:09 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../lib/libft/libft.h"
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
		exit(-1);
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
	char	*tmp;

	while (ft_strnstr(envp->key, "PATH", 4) == 0)
		envp = envp->next;
	paths = ft_split(envp->value, ':');
	if (!paths || !*paths)
		exit(-1);
	free(tmp);
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

void child_process(t_shell *shell)
{
	char *path;
	int result;

	path = find_valid_path(shell->tokens->token, shell->env);
	result = execve(path, shell->cmd->cmd, shell->envp);
	if (result == -1)
		printf("HATA");
	ft_putendl_fd(path, 1);
	exit(0);
}

void execute_cmd(t_shell *shell)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		exit(-1);
	if (pid == 0)
		child_process(shell);
	waitpid(-1, NULL, 0);
}