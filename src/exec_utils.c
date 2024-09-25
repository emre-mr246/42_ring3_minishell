/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:21:13 by emgul             #+#    #+#             */
/*   Updated: 2024/09/25 10:45:04 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include <sys/stat.h>

char	*make_path(char *uncompleted_path, char *cmd)
{
	char	*path_part;
	char	*valid_path;

	path_part = ft_strjoin(uncompleted_path, "/");
	if (!path_part)
		return (NULL);
	valid_path = ft_strjoin(path_part, cmd);
	free(path_part);
	if (!valid_path)
		return (NULL);
	if (access(valid_path, F_OK) < 0)
	{
		free(valid_path);
		return (NULL);
	}
	return (valid_path);
}

char	*find_valid_path(char *cmd, t_env *envp)
{
	int		i;
	char	**paths;
	char	*valid_path;
	t_env	*env_tmp;

	env_tmp = envp;
	while (env_tmp && (ft_strnstr(env_tmp->key, "PATH", higher_len(env_tmp->key, "PATH")) == 0))
		env_tmp = env_tmp->next;
	if (!env_tmp)
	{
		return (NULL);
	}
	paths = ft_split(env_tmp->value, ':');
	if (!paths || !*paths)
	{
		free_array(paths);
		return (NULL);
	}
	i = 0;
	while (paths[i])
	{
		valid_path = make_path(paths[i++], cmd);
		if (valid_path != NULL)
			break ;
	}
	free_array(paths);
	return (valid_path);
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

void	handle_cmd_errors(t_shell *shell, t_cmd *cmd)
{
	struct stat	statbuf;

	stat(cmd->arr[0], &statbuf);
	if (access(cmd->arr[0], X_OK) == -1 && access(cmd->arr[0], F_OK) == 0
		&& ft_strchr(cmd->arr[0], '/'))
	{
		print_error(shell, cmd->arr[0], ERR_NOPERM, 0);
		*shell->exit_status = 126;
	}
	else if (S_ISDIR(statbuf.st_mode) && ft_strchr(cmd->arr[0], '/'))
	{
		print_error(shell, cmd->arr[0], ERR_ISDIR, 0);
		*shell->exit_status = 126;
	}
	else if (access(cmd->arr[0], X_OK) == -1 || (access(cmd->arr[0], X_OK) == 0
			&& S_ISDIR(statbuf.st_mode)))
	{
		print_error(shell, cmd->arr[0], ERR_NOCMD, 0);
		*shell->exit_status = 127;
	}
	else if (access(cmd->arr[0], F_OK))
	{
		print_error(shell, cmd->arr[0], ERR_NODIR, 0);
		*shell->exit_status = 127;
	}
}
