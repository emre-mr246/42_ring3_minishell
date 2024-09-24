/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:25:14 by mitasci           #+#    #+#             */
/*   Updated: 2024/09/24 12:45:46 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include "readline/readline.h"

static void	write_to_outfile(t_cmd *cmd, char *parsed, int *i)
{
	if (cmd->outfile)
		free(cmd->outfile);
	cmd->outfile = parsed;
	cmd->out_redir = get_redirection(cmd->arr[*i]);
}

static void	write_to_infile(t_cmd *cmd, char *parsed, int *i)
{
	if (cmd->infile)
		free(cmd->infile);
	cmd->infile = parsed;
	cmd->in_redir = get_redirection(cmd->arr[*i]);
	if (cmd->in_redir == HERE_DOC)
		add_to_heredoc_arr(cmd, parsed);
}

int	write_to_redir(t_shell *shell, t_cmd *cmd, int *i, int mode_in_out)
{
	char	*parsed;

	parsed = parse_file(shell, cmd->arr[*i + 1]);
	if (mode_in_out == 0)
	{
		write_to_outfile(cmd, parsed, i);
		if (outfile_controls(shell, cmd))
			return (1);
	}
	else if (mode_in_out == 1)
	{
		write_to_infile(cmd, parsed, i);
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
	free_array(cmd->arr);
	cmd->arr = arr;
}
