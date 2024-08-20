/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 22:25:28 by emgul             #+#    #+#             */
/*   Updated: 2024/08/20 19:03:51 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../lib/libft/libft.h"
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

char	*handle_comment(char *str)
{
	while (*str != '\n' || *str)
		str++;
	return (str);
}

char	*handle_quote(char **str, char quote)
{
	int		i;
	char	*res;

	i = 1;
	while ((*str)[i])
	{
		if ((*str)[i] == quote)
		{
			res = ft_substr(*str, 0, i + 1);
			*str += i + 1;
			return (res);
		}
		i++;
	}
	return (NULL);
}

int skip_whitespaces(char **str, int *i)
{
	while ((*str)[*i] == ' ' || ((*str)[*i] >= 8 && (*str)[*i] <= 13)
		|| ((*str)[*i] == '\\'))
	(*i)++;
	return (*i);
}

char	*handle_space(char **str, t_env *env)
{
	int		i;
	char	*res;
	char c;

	i = 0;
	i = skip_whitespaces(str, &i);
	while ((*str)[i])
	{
		if ((*str)[i] == '"' || (*str)[i] == '\'')
		{
			c = (*str)[i];
			i++;
			while ((*str)[i] != c)
				i++;
		}
		if ((*str)[i] == ' ' || ((*str)[i] >= 8 && (*str)[i] <= 13) || (*str)[i] == '\\')
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

char	*get_special_char(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (*input == '&' && *(input + 1) == '&')
			return (ft_strdup("&&"));
		else if (*input == '|' && *(input + 1) == '|')
			return (ft_strdup("||"));
		else if (*input == '<' && *(input + 1) == '<')
			return (ft_strdup("<<"));
		else if (*input == '>' && *(input + 1) == '>')
			return (ft_strdup(">>"));
		else if (*input == '>')
			return (ft_strdup(">"));
		else if (*input == '<')
			return (ft_strdup("<"));
		else if (*input == '|')
			return (ft_strdup("|"));
		i++;
	}
	return (NULL);
}

int	get_indexes(char *input)
{
	int	*indexes;
	int	min_i;
	int	i;

	min_i = INT_MAX;
	indexes = (int *)malloc(sizeof(int) * 7);
	if (!indexes)
		return (-1);
	indexes[0] = ft_find_index(input, "&&");
	indexes[1] = ft_find_index(input, "||");
	indexes[2] = ft_find_index(input, "<<");
	indexes[3] = ft_find_index(input, ">>");
	indexes[4] = ft_find_index(input, "<");
	indexes[5] = ft_find_index(input, ">");
	indexes[6] = ft_find_index(input, "|");
	i = 0;
	while (i < 7)
	{
		if (indexes[i] < min_i && !(indexes[i] == -1))
			min_i = indexes[i];
		i++;
	}
	return (min_i);
}

char	*handle_special_char(char **input)
{
	int		i;
	char	*res;
	char	*tmp;

	i = get_indexes(*input);
	if (i == -1)
		return (NULL);
	else if (i == 0)
	{
		res = get_special_char(*input);
		*input += ft_strlen(res);
		return (res);
	}
	else if (i == INT_MAX)
		return (NULL);
	else
	{
		res = ft_substr(*input, 0, i);
		tmp = ft_strdup(ft_strtrim(res, " "));
		if (ft_strchr(tmp, ' '))
			return (NULL);
		*input += i;
		return (res);
	}
}

t_tokens	*tokenizer(char *input, t_env *env)
{
	char		*res;
	t_tokens	*tokens;

	if (!env)
		return (NULL);
	tokens = NULL;
	while (input && *input)
	{
		res = NULL;
		if ((*input == '\'' || *input == '\"') && input)
			res = handle_quote(&input, *input);
		if (input && !res)
			res = handle_special_char(&input);
		if (input && !res)
			res = handle_space(&input, env);
		if (input && res && ft_strtrim(res, " ") != NULL)
		{
			lstadd_back_token(&tokens, new_token(ft_strtrim(res, "\n\t ")));
			free(res);
		}
		if (input && !res)
			input++;
		while (*input == ' ')
			input++;
	}
	return (tokens);
}
