/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:48:40 by emgul             #+#    #+#             */
/*   Updated: 2024/07/08 14:58:15 by emgul            ###   ########.fr       */
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

char *handle_single_quote(char **str)
{
	int i;
	char	*res;

	i = 0;
	(*str)++;
	while((*str)[i])
	{
		if ((*str)[i] == '\'')
		{
			res = ft_substr(*str, 0, i);
			*str += i + 1;
			return (res);
		}
		i++;
	}
	*str += i;
	return (NULL);
}

char *handle_double_quote(char **str, t_env *env)
{
	int i;
	char	*res;

	i = 0;
	(*str)++;
	while((*str)[i])
	{
		// if (str[i] == '$')
		// 	handle_dollar_sign();
		if ((*str)[i] == '\"')
		{
			res = ft_substr(*str, 0, i);
			*str += i + 1;
			return (res);
		}
		i++;
	}
	*str += i;
	return (NULL);
}

char *handle_space(char **str, t_env *env)
{
	int 	i;
	char	*res;

	i = 0;
	while((*str)[i] == ' ' || ((*str)[i] >= 8 && (*str)[i] <= 13) || ((*str)[i] == '\\'))
		i++;
	while((*str)[i])
	{
		if (((*str)[i] == '\'' || (*str)[i] == '\"') 
		&& ((*str)[i - 1] == ' ' || (*str)[i - 1] == '\n' || (*str)[i - 1] == '\t'))
			return (NULL);
		// if (str[i] == '$')
		// 	handle_dollar_sign();
		if ((*str)[i] == ' ' || ((*str)[i] >= 8 && (*str)[i] <= 13) || ((*str)[i] == '\\'))
		{
			res = ft_substr(*str, 0, i);
			*str += i;
			return (res);
		}
		i++;
	}
	if ((*str)[i] == '\0')
	{
		res = ft_substr(*str, 0, i);
		*str += i;
		return (res);
	}
	*str += i;
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



t_tokens *tokenizer(char *input, t_env *env)
{
	char *res;
	t_tokens *tokens;

	while (*input)
	{
		res = NULL;
		if (*input == '\'')
			res = handle_single_quote(&input);
		if (!res && *input == '\"')
			res = handle_double_quote(&input, env);
		if (!res)
			res = handle_space(&input, env);
		if (res)
		{
			lstadd_back_token(&tokens, new_token(ft_strtrim(res, "\n\t ")));
			free(res);
		}
		if (!res)
			input++;
	}
	return (tokens);
}


int main(int ac, char **av, char **env)
{
	av[0] = "./minishell";
	av[1] = " poğaça       \n	\t		  börek emre'mısra''yeşil çay' içiyor!!";
	av[2] = NULL;
	t_env *environment;
	// environment = get_env(env);
	// tokenizer("ls \"$KEK\" && cat 'test.txt'", environment);
	t_tokens *tokens;
	*av++;
	tokens = tokenizer(*av, environment);
	return (0);
}