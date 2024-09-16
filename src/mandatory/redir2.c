/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:25:08 by mitasci           #+#    #+#             */
/*   Updated: 2024/09/16 15:57:39 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include "readline/readline.h"

int	get_redirection(char *s)
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

int	open_outfile(t_shell *shell, t_cmd *cmd)
{
	int	fd;

	if ((cmd->out_redir == REDIRECT_OUTPUT || cmd->out_redir == APPEND_OUTPUT)
		&& access(cmd->outfile, R_OK) == -1 && access(cmd->outfile, F_OK) == 0)
		print_error(shell, cmd->outfile, ERR_NOPERM, 1);
	if (cmd->out_redir == REDIRECT_OUTPUT)
		fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (cmd->out_redir == APPEND_OUTPUT)
		fd = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = -1;
	return (fd);
}

int	open_infile(t_shell *shell, t_cmd *cmd)
{
	int	fd;

	if (cmd->in_redir == REDIRECT_INPUT && access(cmd->infile, F_OK))
		exit(1);
	if (cmd->in_redir == REDIRECT_INPUT)
		fd = open(cmd->infile, O_RDONLY, 0777);
	else
		fd = -1;
	return (fd);
}

int	outfile_controls(t_shell *shell, t_cmd *cmd)
{
	int fd;
	
	if ((cmd->out_redir == REDIRECT_OUTPUT
			|| cmd->out_redir == APPEND_OUTPUT) && access(cmd->outfile,
			R_OK) == -1 && access(cmd->outfile, F_OK) == 0)
		return (1);
	else if (access(cmd->outfile, F_OK) == -1)
	{
		fd = open_outfile(shell, cmd);
		if (fd != -1)
			close(fd);
	}
	return (0);
}

int	infile_controls(t_shell *shell, t_cmd *cmd)
{
	if (access(cmd->infile, F_OK))
	{
		print_error(shell, cmd->infile, ERR_NODIR, 0);
		return (1);
	}
	else if (access(cmd->infile, R_OK))
	{
		print_error(shell, cmd->infile, ERR_NOPERM, 0);
		return (1);
	}
	return (0);
}
