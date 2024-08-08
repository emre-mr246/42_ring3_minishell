/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:54:12 by emgul             #+#    #+#             */
/*   Updated: 2024/08/08 15:48:18 by emgul            ###   ########.fr       */
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
		cmd = cmd->next;	
		j++;
	}
}
