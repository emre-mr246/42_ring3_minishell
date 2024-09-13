/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:32:18 by emgul             #+#    #+#             */
/*   Updated: 2024/09/13 14:04:18 by emgul            ###   ########.fr       */
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
	return (cmd);
}

static int	get_special_char_enum(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (*input == '&' && *(input + 1) == '&')
			return (AND);
		else if (*input == '|' && *(input + 1) == '|')
			return (OR);
		else if (*input == '|')
			return (PIPE);
		i++;
	}
	return (NONE);
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

static void	check_odd_quotes(t_shell *shell, char *token)
{
	int		single_quote_num;
	int		double_quote_num;
	bool	single_quote;
	bool	double_quote;
	int		i;

	single_quote_num = 0;
	double_quote_num = 0;
	i = -1;
	while (token[++i])
	{
		if (token[i] == '\"' && !single_quote)
		{
			double_quote = !double_quote;
			double_quote_num++;
		}
		if (token[i] == '\'' && !double_quote)
		{
			single_quote = !single_quote;
			single_quote_num++;
		}
	}
	if (double_quote_num % 2 != 0 || single_quote_num % 2 != 0)
		print_error(shell, NULL, NULL, ERR_QUOTES, 1);
}

static void	*create_cmd(t_shell *shell, t_cmd **cmd, t_tokens *token, int *i)
{
	int		special_char;
	
	special_char = get_special_char_enum(token->token);
	if (special_char)
	{
		//printf("i: %i\n", *i);
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
	int		i;

	i = 0;
	cmd = new_cmd(NULL);
	cmd_tmp = cmd;
	while (1)
	{
		create_cmd(shell, &cmd, token, &i);
		if (token->token)
			free(token->token);
		if (token->next)
			token = token->next;
		else
			break ;
	}
	free(token);
	return (cmd_tmp);
}
