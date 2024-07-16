/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 22:25:28 by emgul             #+#    #+#             */
/*   Updated: 2024/07/10 22:28:59 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include "../lib/libft/libft.h"

char	*handle_comment(char *str)
{
	while (*str != '\n' || *str)
		str++;
	return (str);
}

char	*handle_single_quote(char **str)
{
	int		i;
	char	*res;

	i = 0;
	(*str)++;
	while ((*str)[i])
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

char	*handle_double_quote(char **str, t_env *env)
{
	int		i;
	char	*res;

	i = 0;
	(*str)++;
	while ((*str)[i])
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

char	*handle_space(char **str, t_env *env)
{
	int		i;
	char	*res;

	i = 0;
	while ((*str)[i] == ' ' || ((*str)[i] >= 8 && (*str)[i] <= 13)
		|| ((*str)[i] == '\\'))
		i++;
	while ((*str)[i])
	{
		if (((*str)[i] == '\'' || (*str)[i] == '\"') && ((*str)[i - 1] == ' '
				|| (*str)[i - 1] == '\n' || (*str)[i - 1] == '\t'))
			return (NULL);
		// if (str[i] == '$')
		// 	handle_dollar_sign();
		if ((*str)[i] == ' ' || ((*str)[i] >= 8 && (*str)[i] <= 13)
			|| ((*str)[i] == '\\'))
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

char *handle_ampersand(char **input)
{
	int i;
	char *res;

	i = ft_find_index(*input, "&&");
	if (i == -1)
		return (NULL);
	if (i == 0)
	{
		*input += 2;
		return (ft_strdup("&&"));
	}
	else
	{
		res = ft_substr(*input, 0, i);
		if (ft_strchr(res, ' '))
			return (NULL);
		*input += i;
		return (res);
	}
}

t_tokens	*tokenizer(char *input, t_env *env)
{
	char		*res;
	t_tokens	*tokens;

	tokens = NULL;
	if (!env)
		return (NULL);
	while (*input)
	{
		res = NULL;
		if (*input == '\'')
			res = handle_single_quote(&input);
		if (!res && *input == '\"')
			res = handle_double_quote(&input, env);
		if (!res)
			res = handle_ampersand(&input);
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
