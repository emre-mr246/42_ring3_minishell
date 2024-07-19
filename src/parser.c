/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kali <kali@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:48:40 by emgul             #+#    #+#             */
/*   Updated: 2024/07/16 13:38:15 by kali             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../lib/libft/libft.h"
#include "readline/history.h"
#include "readline/readline.h"
#include <fcntl.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <limits.h>
#include <linux/limits.h>

t_cmd *init_cmd()
{
    t_cmd *cmd;
    
    cmd = (t_cmd *)malloc(sizeof(t_cmd));
    if (!cmd)
        return (NULL);
    cmd->cmd = (char **)malloc(ARG_MAX);
    if (!cmd->cmd)
        return (NULL);
    cmd->special_char = NONE;
    cmd->next = NULL;
    return (cmd);
}

int get_special_char_enum(char *input)
{
	int i;

	i = 0;
	while (input[i])
	{
		if (*input == '&' && *(input + 1) == '&')
			return (AND);
		else if (*input == '|' && *(input + 1) == '|')
			return (OR);		
		else if (*input == '<' && *(input + 1) == '<')
			return (HERE_DOC);
		else if (*input == '>' && *(input + 1) == '>')
			return (APPEND_OUTPUT);
		else if (*input == '>')
			return (REDIRECT_OUTPUT);
		else if (*input == '<')
			return (REDIRECT_INPUT);
		else if (*input == '|')
			return (PIPE);
		i++;
	}
	return (NONE);
}

t_cmd	*parser(t_tokens token)
{
	t_cmd	*cmd;
    t_cmd *cmd_tmp;
	int		i;
    int special_char;

	i = 0;
    cmd = new_cmd(NULL);
    cmd_tmp = cmd;
	while (1)
	{
        special_char = get_special_char_enum(token.token);
        if (special_char)
        {
            cmd->special_char = special_char;
            lstadd_back_cmd(&cmd, new_cmd(NULL));
            cmd = cmd->next;
            i = 0;
        }
        else
        {
            cmd->cmd[i] = ft_strdup(token.token);
        	i++;
        }
        if (token.next)
            token = *token.next;
		else
            break ;
	}
    lstadd_back_cmd(&cmd, new_cmd(NULL));
	return (cmd_tmp);
}


// ls -la && grep kek > sonuc.txt