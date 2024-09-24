/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:40:32 by emgul             #+#    #+#             */
/*   Updated: 2024/09/24 13:47:13 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include "readline/readline.h"

void	redirect_files(t_shell *shell, t_cmd *cmd)
{
	int	outfd;
	int	infd;

	outfd = open_outfile(shell, cmd);
	if (cmd->in_redir != HERE_DOC)
		infd = open_infile(cmd);
	else
		infd = -1;
	if (outfd != -1 && (cmd->out_redir == REDIRECT_OUTPUT
			|| cmd->out_redir == APPEND_OUTPUT))
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
		redir_heredoc();
}

void	redirect_pipes(int fd[][2], int cmdlen, int i)
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

char	*parse_file(t_shell *shell, char *file)
{
	bool	single_quote;
	bool	double_quote;
	int		i;
	int		j;
	char	*new;

	single_quote = false;
	double_quote = false;
	new = allocate_str(shell, BUFFER_SIZE);
	i = 0;
	j = 0;
	while (file[i])
	{
		if (file[i] == '\'' && !double_quote)
			single_quote = !single_quote;
		else if (file[i] == '"' && !single_quote)
			double_quote = !double_quote;
		else if ((single_quote && file[i] != '\'') \
		|| (double_quote && file[i] != '"') \
		|| (!single_quote && !double_quote))
			new[j++] = file[i];
		i++;
	}
	return (new);
}
