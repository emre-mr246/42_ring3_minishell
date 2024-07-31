/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 22:26:42 by emgul             #+#    #+#             */
/*   Updated: 2024/07/31 08:28:36 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include "../../lib/libft/libft.h"

t_tokens	*new_token(char *token)
{
	t_tokens	*tokens;

	tokens = (t_tokens *)malloc(sizeof(t_tokens));
	if (!tokens)
		return (NULL);
	tokens->next = NULL;
	if (!token)
		tokens->token = NULL;
	else
		tokens->token = token;
	return (tokens);
}

void	lstadd_back_token(t_tokens **lst, t_tokens *new)
{
	t_tokens	*tmp;

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

	cmds = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmds)
		return (NULL);
	cmds->next = NULL;
	if (!cmd)
		cmds->cmd = (char **)malloc(ARG_MAX);
	else
		cmds->cmd = cmd;
	cmds->special_char = NONE;
	cmds->is_builtin = false;
	return (cmds);
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

int	ft_find_index(char *haystack, char *needle)
{
	int	i;
	int	j;
	int	tmp;
	int needle_len;

	needle_len = ft_strlen(needle);
	i = 0;
	while (haystack[i])
	{
    	tmp = i;
        j = 0;
		while (haystack[tmp] == needle[j])
		{
			if (j + 1 == needle_len)
				return (i);
            tmp++;
			j++;
		}
		i++;
	}
	return (-1);
}
