/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:48:40 by emgul             #+#    #+#             */
/*   Updated: 2024/07/05 14:21:35 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline/readline.h"
#include "readline/history.h"
#include "../lib/libft/libft.h"
#include "../inc/minishell.h"

char *handle_comment(char *str)
{
	while(*str != '\n' || *str)
		str++;
	return (str);
}

char *handle_single_quote(char *str)
{
	int i;
	char	*res;

	i = 0;
	while(str[i])
	{
		if (str[i] == '\'')
		{
			res = ft_substr(str, 0, i);
			return (res);
		}
		i++;
	}
	return (NULL);
}

char *handle_double_quote(char *str, t_env *env)
{
	int i;
	char	*res;

	i = 0;
	while(str[i])
	{
		// if (str[i] == '$')
		// 	handle_dollar_sign();
		if (str[i] == '\"')
		{
			res = ft_substr(str, 0, i);
			return (res);
		}
		i++;
	}
	return (NULL);
}

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

void	ft_lstadd_back_token(t_tokens **lst, t_tokens *new)
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

char **tokenizer(char *input, t_env *env)
{
	int i;
	char *res;
	t_tokens *tokens;

	i = 0;
	tokens = new_token("maymun");
	while (input[i])
	{
		if (input[i] == '\'')
			res = handle_single_quote(&input[i + 1]);
		if (input[i] == '\"')
			res = handle_double_quote(&input[i + 1], env);
		if (res)
			i += ft_strlen(res) + 2;
		else
			i++;
		printf("SONUC: %s ve İ: %i\n", res, i);
	}
}


int main(int ac, char **av, char **env)
{
	t_env *environment;
	// environment = get_env(env);
	// tokenizer("ls \"$KEK\" && cat 'test.txt'", environment);
	t_tokens *tokens;
	tokens = new_token("kek");
	ft_lstadd_backs(tokens, new_token("borek"));
	ft_lstadd_backs(tokens, new_token("elma"));
	int elma = 5;
	return (0);
}