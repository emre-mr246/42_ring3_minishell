/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:25:14 by mitasci           #+#    #+#             */
/*   Updated: 2024/09/21 13:44:03 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include "readline/readline.h"

static void add_to_heredoc_arr(t_cmd *cmd, char *str)
{
	int i;

	i = 0;
	while (cmd->heredoc_arr[i])
		i++;
	cmd->heredoc_arr[i] = ft_strdup(str);
	i++;
	cmd->heredoc_arr[i] = NULL;
}

int	write_to_redir(t_shell *shell, t_cmd *cmd, int *i, int mode_in_out)
{
	char	*parsed;

	parsed = parse_file(shell, cmd, cmd->arr[*i + 1]);
	if (mode_in_out == 0)
	{
		if (cmd->outfile)
			free(cmd->outfile);
		cmd->outfile = parsed;
		cmd->out_redir = get_redirection(cmd->arr[*i]);
		if (outfile_controls(shell, cmd))
			return (1);
	}
	else if (mode_in_out == 1)
	{
		if (cmd->infile)
			free(cmd->infile);
		cmd->infile = parsed;
		cmd->in_redir = get_redirection(cmd->arr[*i]);
		if (cmd->in_redir == HERE_DOC)
			add_to_heredoc_arr(cmd, parsed);
		if (infile_controls(shell, cmd))
			return (1);
	}
	if (cmd->arr[*i + 2])
		*i += 2;
	else
		return (1);
	return (0);
}

void	remove_redir(t_shell *shell, t_cmd *cmd, char **arr)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (cmd->arr[i])
	{
		if (ft_strncmp(cmd->arr[i], ">", 1) == 0)
		{
			if (write_to_redir(shell, cmd, &i, 0))
				break ;
		}
		else if (ft_strncmp(cmd->arr[i], "<", 1) == 0)
		{
			if (write_to_redir(shell, cmd, &i, 1))
				break ;
		}
		else
		{
			arr[j++] = ft_strdup(cmd->arr[i++]);
		}
	}
	arr[j] = NULL;
}

void	remove_redirs(t_shell *shell, t_cmd *cmd)
{
	char	**arr;

	arr = (char **)ft_calloc(sizeof(char *), ARG_MAX);
	if (!arr)
		return ;
	remove_redir(shell, cmd, arr);
	int i = 0;
	// while (cmd->heredoc_arr[i])
	// 	printf("str: %s\n", cmd->heredoc_arr[i++]);
	free_array(cmd->arr);
	cmd->arr = arr;
}

void	heredoc(t_cmd *cmd)
{
	char	*line;
	char	*delim;
	int		tmpfd;
	int		i;

	tmpfd = open(HEREDOC_TMP_PATH, O_CREAT | O_RDWR, 0644);
	i = 0;
	line = NULL;
	while (1)
	{
		delim = cmd->heredoc_arr[i];
		if (!delim)
			break ;
		line = readline(">");
		printf("line: %s\n", line);
		printf("delim: %s\n", delim);
		if (!line)
		{
			close(tmpfd);
			return ;
		}
		if (ft_strncmp(line, delim, higher_len(line, delim)) == 0)
		{
			i++;
			free(line);
			continue ;
		}
		if (!str_in_array(cmd->heredoc_arr, line))
			ft_putendl_fd(line, tmpfd);
		free(line);
	}
	close(tmpfd);
}

void	redir_heredoc(t_shell *shell, t_cmd *cmd)
{
	int	infd;

	infd = open(HEREDOC_TMP_PATH, O_RDONLY, 0644);
	if (infd != -1)
	{
		dup2(infd, STDIN_FILENO);
		close(infd);
		unlink(HEREDOC_TMP_PATH);
	}
}
