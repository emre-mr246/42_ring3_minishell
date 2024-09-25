/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:32:18 by emgul             #+#    #+#             */
/*   Updated: 2024/09/25 16:02:57 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

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

t_cmd	*new_cmd(t_shell *shell, char **arr)
{
	t_cmd	*cmds;

	cmds = (t_cmd *)ft_calloc(1, sizeof(t_cmd));
	if (!cmds)
		return (NULL);
	if (!arr)
	{
		cmds->arr = (char **)ft_calloc(sizeof(char *), ARG_MAX);
		if (!cmds->arr)
			return (NULL);
	}
	else
		cmds->arr = arr;
	cmds->special_char = NONE;
	cmds->is_builtin = false;
	cmds->out_redir = NONE_REDIR;
	cmds->in_redir = NONE_REDIR;
	cmds->outfile = NULL;
	cmds->infile = NULL;
	cmds->next = NULL;
	cmds->shell = shell;
	cmds->heredoc_arr = (char **)ft_calloc(sizeof(char *), ARG_MAX);
	if (!cmds->heredoc_arr)
		return (NULL);
	return (cmds);
}

static void	create_cmd(t_shell *shell, t_cmd **cmd, t_tokens *token, int *i)
{
	int	special_char;

	special_char = get_special_char_enum(token->token);
	if (special_char)
	{
		(*cmd)->arr[*i] = NULL;
		(*cmd)->special_char = special_char;
		lstadd_back_cmd(cmd, new_cmd(shell, NULL));
		*cmd = (*cmd)->next;
		*i = 0;
	}
	else
	{
		(*cmd)->arr[*i] = ft_strdup(token->token);
		(*i)++;
	}
	return ;
}

t_cmd	*create_cmds(t_shell *shell, t_tokens token)
{
	t_cmd	*cmd;
	t_cmd	*cmd_tmp;
	int		i;

	i = 0;
	cmd = new_cmd(shell, NULL);
	cmd_tmp = cmd;
	while (1)
	{
		create_cmd(shell, &cmd, &token, &i);
		if (token.next)
			token = *token.next;
		else
			break ;
	}
	return (cmd_tmp);
}
