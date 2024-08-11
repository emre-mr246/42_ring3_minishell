/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:54:12 by emgul             #+#    #+#             */
/*   Updated: 2024/08/11 23:43:06 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../lib/libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

void print_cmd(t_shell *shell)
{
	t_cmd *cmd;
	int i;
	int j;
	
	j = 0;
	cmd = shell->cmd;
	while (cmd)
	{
		i = 0;
		while (cmd->arr[i])
		{
			printf("CMD %i: %s\n", j, cmd->arr[i]);
			i++;
		}
		printf("Special Char: %i\n", cmd->special_char);
		if (cmd->infile && cmd->in_redir)
			printf("INFILE: %s, IN_REDIR: %i\n", cmd->infile, cmd->in_redir);
		if (cmd->outfile && cmd->out_redir)
			printf("OUTFILE: %s, OUT_REDIR: %i\n", cmd->outfile, cmd->out_redir);
		cmd = cmd->next;	
		j++;
	}
}
