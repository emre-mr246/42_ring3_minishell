/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 13:54:12 by emgul             #+#    #+#             */
/*   Updated: 2024/08/02 13:55:37 by emgul            ###   ########.fr       */
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
	
	cmd = shell->cmd;
	i = 0;
	while (cmd->arr[i])
	{
		printf("CMD: %s\n", cmd->arr[i]);
		i++;
	}
}
