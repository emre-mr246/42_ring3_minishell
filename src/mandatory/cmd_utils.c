/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:32:17 by emgul             #+#    #+#             */
/*   Updated: 2024/08/08 13:49:27 by emgul            ###   ########.fr       */
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

int cmd_len(t_cmd *cmd)
{
	t_cmd *tmp;
	int len;

	tmp = cmd;
	len = 0;
	while(tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

