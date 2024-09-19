/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:32:18 by emgul             #+#    #+#             */
/*   Updated: 2024/09/19 19:08:29 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->arr = (char **)ft_calloc(sizeof(char *), ARG_MAX);
	if (!cmd->arr)
		return (NULL);
	cmd->special_char = NONE;
	cmd->is_builtin = false;
	cmd->out_redir = NONE_REDIR;
	cmd->in_redir = NONE_REDIR;
	cmd->outfile = NULL;
	cmd->infile = NULL;
	return (cmd);
}

void	lstadd_back_cmd(t_cmd **lst, t_cmd *new)
{
	t_cmd	*tmp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return ;
}

t_cmd	*new_cmd(char **cmd)
{
	t_cmd	*cmds;

	cmds = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!cmds)
		return (NULL);
	if (!cmd)
	{
		cmds->arr = (char **)ft_calloc(sizeof(char *), ARG_MAX);
		if (!cmds->arr)
			return (NULL);
	}
	else
		cmds->arr = cmd;
	return (cmds);
}


static void	create_cmd(t_shell *shell, t_cmd **cmd, t_tokens *token, int *i)
{
	int		special_char;
	
	special_char = get_special_char_enum(token->token);
	if (special_char)
	{
		(*cmd)->arr[*i] = NULL;
		(*cmd)->special_char = special_char;
		lstadd_back_cmd(cmd, new_cmd(NULL));
		*cmd = (*cmd)->next;
		*i = 0;
	}
	else
	{
		check_odd_quotes(shell, token->token);
		(*cmd)->arr[*i] = ft_strdup(token->token);
		(*i)++;
	}
}

t_cmd	*create_cmds(t_shell *shell, t_tokens *token)
{
	t_cmd	*cmd;
	t_cmd	*cmd_tmp;
	t_tokens	*token_tmp;
	int		i;

	i = 0;
	cmd = new_cmd(NULL);
	cmd_tmp = cmd;
	token_tmp = token;
	while (1)
	{
		create_cmd(shell, &cmd, token, &i);
		if (token->next)
			token = token->next;
		else
			break ;
	}
	return (cmd_tmp);
}
