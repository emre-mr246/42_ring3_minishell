/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:40:37 by emgul             #+#    #+#             */
/*   Updated: 2024/09/17 18:33:44 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

t_tokens	*new_token(char *token)
{
	t_tokens	*tokens;

	tokens = (t_tokens *)ft_calloc(sizeof(t_tokens), 1);
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

void	free_token(t_tokens *token)
{
	t_tokens	*tmp;

	while (token)
	{
		tmp = token->next;
		free(token->token);
		free(token);
		token = tmp;
	}
}
