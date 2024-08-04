/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 22:26:42 by emgul             #+#    #+#             */
/*   Updated: 2024/08/04 21:59:51 by emgul            ###   ########.fr       */
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
		cmds->arr = (char **)malloc(ARG_MAX);
	else
		cmds->arr = cmd;
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

int max_len(char *str1, char *str2)
{
	int len1;
	int len2;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	if (len1 > len2)
		return (len1);
	else
		return (len2);
}
