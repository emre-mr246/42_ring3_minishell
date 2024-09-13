/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:40:32 by emgul             #+#    #+#             */
/*   Updated: 2024/09/13 14:08:55 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>

static int	get_redirection(char *s)
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
		print_error(shell, cmd->outfile, NULL, ERR_NOPERM, 1);
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
		print_error(shell, cmd->infile, NULL, ERR_NODIR, 0);
		return (1);
	}
	else if (access(cmd->infile, R_OK))
	{
		print_error(shell, cmd->infile, NULL, ERR_NOPERM, 0);
		return (1);
	}
	return (0);
}

int	write_to_redir(t_shell *shell, t_cmd *cmd, int *i, int mode_in_out)
{
	char	*parsed;

	parsed = parse_file(shell, cmd, cmd->arr[*i + 1]);
	if (mode_in_out == 0)
	{
		cmd->outfile = parsed;
		cmd->out_redir = get_redirection(cmd->arr[*i]);
		if (outfile_controls(shell, cmd))
			return (1);
	}
	if (mode_in_out == 1)
	{
		cmd->infile = parsed;
		cmd->in_redir = get_redirection(cmd->arr[*i]);
		if (infile_controls(shell, cmd))
			return (1);
	}
	if (cmd->arr[*i + 2])
	{
		*i += 2;
	}
	else
		return (1);
	return (0);
}

static void	remove_redir(t_shell *shell, t_cmd *cmd, char **arr)
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
	int i;
	int j;
	char **arr;

	arr = (char **)ft_calloc(sizeof(char *), ARG_MAX);
	if (!arr)
		return ;
	remove_redir(shell, cmd, arr);
	free_array(cmd->arr);
	cmd->arr = arr;
}