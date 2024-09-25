/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:37:35 by mitasci           #+#    #+#             */
/*   Updated: 2024/09/25 12:42:28 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include "readline/readline.h"

void	add_to_heredoc_arr(t_cmd *cmd, char *str)
{
	int	i;

	i = 0;
	while (cmd->heredoc_arr[i])
		i++;
	cmd->heredoc_arr[i] = ft_strdup(str);
	i++;
	cmd->heredoc_arr[i] = NULL;
}

int	heredoc_loop(int *i, int tmpfd, t_cmd *cmd)
{
	char	*delim;
	char	*line;

	delim = cmd->heredoc_arr[*i];
	if (!delim)
		return (1);
	line = readline(">");
	if (!line)
		return (1);
	if (ft_strncmp(line, delim, higher_len(line, delim)) == 0)
	{
		(*i)++;
		free(line);
		return (0);
	}
	if (!str_in_array(cmd->heredoc_arr, line))
		ft_putendl_fd(line, tmpfd);
	free(line);
	return (0);
}

void	heredoc(t_cmd *cmd)
{
	int		tmpfd;
	int		i;

	tmpfd = open(HEREDOC_TMP_PATH, O_CREAT | O_RDWR, 0644);
	i = 0;
	while (1)
	{
		if (heredoc_loop(&i, tmpfd, cmd) == 0)
			continue ;
		else
			break ;
	}
	close(tmpfd);
}

void	redir_heredoc(void)
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
