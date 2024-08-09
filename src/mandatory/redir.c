/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:40:32 by emgul             #+#    #+#             */
/*   Updated: 2024/08/09 15:05:58 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../lib/libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

static int get_redirection(char *s)
{
	if (strncmp(s, ">", higher_len(s, ">")) == 0)
		return (REDIRECT_OUTPUT);
	else if (strncmp(s, ">>", higher_len(s, ">>")) == 0)
		return (APPEND_OUTPUT);
	else if (strncmp(s, "<", higher_len(s, "<")) == 0)
		return (REDIRECT_INPUT);
	else if (strncmp(s, "<<", higher_len(s, "<<")) == 0)
		return (HERE_DOC);
	return (NONE_REDIR);
}

int open_redirfile(t_cmd *cmd)
{
	int fd;

	if (cmd->redirection == REDIRECT_OUTPUT)
		fd = open(cmd->redir_file, O_WRONLY | O_CREAT);
	else if (cmd->redirection == APPEND_OUTPUT)
		fd = open(cmd->redir_file, O_APPEND | O_CREAT);
	else if (cmd->redirection == REDIRECT_INPUT)
		fd = open(cmd->redir_file, O_RDONLY | O_CREAT);
	else
		fd = -1;
	return (fd);
}

static void remove_redir(t_cmd *cmd, char **arr)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	while (cmd->arr[i])
	{
		if (strncmp(cmd->arr[i], ">", higher_len(cmd->arr[i], ">")) == 0
			|| strncmp(cmd->arr[i], ">>", higher_len(cmd->arr[i], ">>")) == 0
			|| strncmp(cmd->arr[i], "<", higher_len(cmd->arr[i], "<")) == 0
			|| strncmp(cmd->arr[i], "<<", higher_len(cmd->arr[i], "<<")) == 0)
		{
			cmd->redir_file = ft_strdup(cmd->arr[i + 1]);
			cmd->redirection = get_redirection(cmd->arr[i]);
			if (cmd->arr[i + 1] && cmd->arr[i + 2])
				i += 2;
			else
				break;
		}
		arr[j] = ft_strdup(cmd->arr[i]);
		free(cmd->arr[i]);
		i++;
		j++;
	}
	arr[j] = NULL;
}

void update_cmdarr(t_shell *shell)
{
	int		i;
	int		j;
	t_cmd	*cmd;
	char	**arr;

	cmd = shell->cmd;
	while(cmd)
	{
		arr = (char **)ft_calloc(sizeof(char *), ARG_MAX);
		if (!arr)
			return ;
		remove_redir(cmd, arr);
		if (!*arr)
			free(arr);
		free(cmd->arr);
		cmd->arr = arr;
		cmd = cmd->next;
	}
}