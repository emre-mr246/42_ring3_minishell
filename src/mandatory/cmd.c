/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:48:40 by emgul             #+#    #+#             */
/*   Updated: 2024/08/08 12:32:10 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../lib/libft/libft.h"
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
    
    cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
    if (!cmd)
        return (NULL);
    cmd->arr = (char **)ft_calloc(1, ARG_MAX);
    if (!cmd->arr)
        return (NULL);
    cmd->special_char = NONE;
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

t_cmd	*create_cmd(t_tokens token)
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
            cmd->arr[i] = ft_strdup(token.token);
        	i++;
        }
        cmd->arr[i] = NULL;
        if (token.next)
            token = *token.next;
		else
            break ;
	}
	return (cmd_tmp);
}

void handle_dollar_sign(char **cmd, t_env *env)
{
	int i;
	char *res;

	i = 0;
	while(cmd[i])
	{
		res = exchange_variable(cmd[i], env);
		cmd[i] = ft_strdup(res);
		i++;
	}
}

void dollar_sign(t_shell *shell)
{
	t_cmd *cmd;
	t_cmd *tmp;

	tmp = shell->cmd;
	while(tmp)
	{
		handle_dollar_sign(tmp->arr, shell->env);
		tmp = tmp->next;
	}
}
