/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 22:25:28 by emgul             #+#    #+#             */
/*   Updated: 2024/09/16 15:38:35 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <limits.h>

char	*handle_space(char **str)
{
	int		i;
	char	*res;

	i = 0;
	skip_whitespaces(str, &i);
	while ((*str)[i])
	{
		skip_quotes(str, &i);
		if ((*str)[i] == ' ' || ((*str)[i] >= 8 && (*str)[i] <= 13)
			|| (*str)[i] == '\\')
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
	indexes = (int *)ft_calloc(sizeof(int), 7);
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
	free(indexes);
	return (min_i);
}

char	*handle_special_char(char **input)
{
	int		i;
	char	*res;
	char	*tmp;
	char *trimmed;

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
		trimmed = ft_strtrim(res, " ");
		tmp = ft_strdup(trimmed);
		free(trimmed);
		if (ft_strchr(tmp, ' '))
			return (NULL);
		free(tmp);
		*input += i;
		return (res);
	}
}

t_tokens	*tokenizer(char *input, t_env *env)
{
	char		*res;
	t_tokens	*tokens;

	tokens = NULL;
	while (input && *input && env)
	{
		res = NULL;
		if ((*input == '\'' || *input == '\"') && input)
			res = handle_quote(&input, *input);
		if (input && !res)
			res = handle_special_char(&input);
		if (input && !res)
			res = handle_space(&input);
		if (input && res)
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
