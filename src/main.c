/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:48:40 by emgul             #+#    #+#             */
/*   Updated: 2024/07/08 13:29:26 by emgul            ###   ########.fr       */
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

char *handle_space(char *str, t_env *env)
{
	int 	i;
	char	*res;

	i = 0;
	while(str[i] == ' ')
		i++;
	while(str[i])
	{
		// if (str[i] == '$')
		// 	handle_dollar_sign();
		if (str[i] == ' ')
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

int skip_spaces(char *input, int *i)
{
	while (*input == ' ')
	{
		*i++;
		input++;
	}
}

t_tokens *tokenizer(char *input, t_env *env)
{
	int i;
	char *res;
	t_tokens *tokens;

	i = 0;
	while (input[i])
	{
		res = NULL;
		skip_spaces((input + i), &i);
		if (input[i] == '\'')
		{
			res = handle_single_quote(&input[i + 1]);
			i += 2;
		}
		skip_spaces((input + i), &i);
		if (!res && input[i] == '\"')
		{
			res = handle_double_quote(&input[i + 1], env);
			i += 2;
		}
		if (!res && (input[i] == ' ' || i == 0))
			res = handle_space(&input[i], env);
		if (res)
		{
			i += ft_strlen(res);
			lstadd_back_token(&tokens, new_token(res));
		}
		else
			i++;
	}
	printf("SONUC: %s ve İ: %i\n", tokens->token, i);
}


int main(int ac, char **av, char **env)
{
	av[0] = "./minishell";
	av[1] = "mısra kahve 'içiyor' 've' !@=2emre       'yeşil çay' içiyor!!";
	av[2] = NULL;
	t_env *environment;
	// environment = get_env(env);
	// tokenizer("ls \"$KEK\" && cat 'test.txt'", environment);
	t_tokens *tokens;
	*av++;
	tokens = tokenizer(*av, environment);
	return (0);
}