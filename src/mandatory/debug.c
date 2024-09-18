/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:54:12 by emgul             #+#    #+#             */
/*   Updated: 2024/09/18 21:36:20 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>

void	print_cmd(t_shell *shell)
{
	t_cmd	*cmd;
	int		i;
	int		j;

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
			printf("OUTFILE: %s, OUT_REDIR: %i\n", cmd->outfile,
				cmd->out_redir);
		cmd = cmd->next;
		j++;
	}
}

void	print_token(t_tokens *token)
{
	t_tokens *tmp;

	tmp = token;
	int i = 0;
	while (tmp)
	{
		printf("token %i: %s\n", i, tmp->token);
		tmp = tmp->next;
		i++;
	}
}