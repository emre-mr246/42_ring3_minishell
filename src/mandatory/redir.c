/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:40:32 by emgul             #+#    #+#             */
/*   Updated: 2024/08/15 19:14:13 by emgul            ###   ########.fr       */
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
	if (ft_strncmp(s, ">", higher_len(s, ">")) == 0)
		return (REDIRECT_OUTPUT);
	else if (ft_strncmp(s, ">>", higher_len(s, ">>")) == 0)
		return (APPEND_OUTPUT);
	else if (ft_strncmp(s, "<", higher_len(s, "<")) == 0)
		return (REDIRECT_INPUT);
	else if (ft_strncmp(s, "<<", higher_len(s, "<<")) == 0)
		return (HERE_DOC);
	return (NONE_REDIR);
}

int open_outfile(t_cmd *cmd)
{
	int fd;

	fd = -1;
	if (cmd->out_redir == REDIRECT_OUTPUT)
		fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (cmd->out_redir == APPEND_OUTPUT)
		fd = open(cmd->outfile, O_APPEND | O_CREAT, 0777);
	else
		fd = -1;
	return (fd);
}

int open_infile(t_cmd *cmd)
{
	int fd;
	
	if (cmd->in_redir == REDIRECT_INPUT)
		fd = open(cmd->infile, O_RDONLY, 0777);
	else
		fd = -1;
	return (fd);
}

int	write_to_redir(t_cmd *cmd, int *i, int mode_in_out)
{
	if (mode_in_out == 0)
	{
		cmd->outfile = ft_strdup(cmd->arr[*i + 1]);
		cmd->out_redir = get_redirection(cmd->arr[*i]);
		if (cmd->arr[*i + 1] && cmd->arr[*i + 2])
		{
			free(cmd->arr[*i]);
			*i += 2;
		}
		else
			return (1);
	}
	if (mode_in_out == 1)
	{
		cmd->infile = ft_strdup(cmd->arr[*i + 1]);
		cmd->in_redir = get_redirection(cmd->arr[*i]);
		if (cmd->arr[*i + 1] && cmd->arr[*i + 2])
		{
			free(cmd->arr[*i]);
			*i += 2;
		}
		else
			return (1);
	}
	return (0);
}

static void remove_redir(t_cmd *cmd, char **arr)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	while (cmd->arr[i])
	{
		if (ft_strncmp(cmd->arr[i], ">", 1) == 0)
		{
			if (write_to_redir(cmd, &i, 0))
				break ;
		}
		else if (ft_strncmp(cmd->arr[i], "<", 1) == 0)
		{
			if (write_to_redir(cmd, &i, 1))
				break ;
		}
		else
		{
			arr[j++] = ft_strdup(cmd->arr[i]);
			free(cmd->arr[i++]);
		}
	}
	arr[j] = NULL;
}

void remove_redirs(t_shell *shell)
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