/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 22:25:28 by emgul             #+#    #+#             */
/*   Updated: 2024/09/19 19:09:39 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <limits.h>

int	is_sp(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

void handle_space(char **res, char **str)
{
	int		i;

	i = 0;
	skip_whitespaces(str, &i);
	while ((*str)[i])
	{
		skip_quotes(str, &i);
		if ((*str)[i] == ' ' || ((*str)[i] >= 8 && (*str)[i] <= 13)
			|| (*str)[i] == '\\' || is_sp((*str)[i]))
		{
			ft_strlcpy(*res, *str, i + 1);
			*res += i;
			*str += i;
			return ;
		}
		i++;
	}
	if ((*str)[i] == '\0')
	{
		ft_strlcpy(*res, *str, i + 1);
		*res += i;
		*str += i;
		return ;
	}
	*str += i;
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

int handle_special_char(char **res, char **input)
{
	int		i;
	char	*sp_char;
	char	*sub;
	char	*trimmed;

	i = get_indexes(*input);
	if (i == -1 || i == INT_MAX)
		return (i);
	else if (i == 0)
	{
		sp_char = get_special_char(*input);
		ft_strlcpy(*res, sp_char, ft_strlen(sp_char) + 1);
		*res += ft_strlen(sp_char);
		*input += ft_strlen(sp_char);
		free(sp_char);
	}
	return (i);
}



void	check_syntax(t_shell *shell, t_tokens *token)
{
	t_tokens *tmp;
	
	tmp = token;
	if (ft_strncmp(tmp->token, "|", 1) == 0)
		print_error(shell, NULL, ERR_SYNTAX, 1);
	while (tmp && tmp->next)
	{
		if (ft_strncmp(tmp->token, "<", 1) == 0 && ft_strncmp(tmp->next->token, "|", 1) == 0)
			print_error(shell, NULL, ERR_SYNTAX, 1);
		if (ft_strncmp(tmp->token, ">", 1) == 0 && ft_strncmp(tmp->next->token, "|", 1) == 0)
			print_error(shell, NULL, ERR_SYNTAX, 1);
		tmp = tmp->next;
	}
	if (ft_strncmp(tmp->token, "|", 1) == 0)
		print_error(shell, NULL, ERR_SYNTAX, 1);
	if (ft_strncmp(tmp->token, "<", 1) == 0)
		print_error(shell, NULL, ERR_SYNTAX, 1);
	if (ft_strncmp(tmp->token, ">", 1) == 0)
		print_error(shell, NULL, ERR_SYNTAX, 1);
}

t_tokens	*tokenizer(t_shell *shell, char *input, t_env *env)
{
	char		*res;
	char		*res_tmp;
	t_tokens	*tokens;
	int			res_i;

	tokens = NULL;
	while (input && *input && env)
	{
		while (*input == ' ')
			input++;
		res = (char *)ft_calloc(sizeof(char), BUFFER_SIZE);
		if (!res)
			return (NULL);
		res_i = 1;
		res_tmp = res;
		if ((*input == '\'' || *input == '\"') && input)
			res_i = handle_quote(&res_tmp, &input, *input);
		if (input && res_i)
			res_i = handle_special_char(&res_tmp, &input);
		if (input && res_i)
			handle_space(&res_tmp, &input);
		*res_tmp = '\0';
		if (input && res)
			lstadd_back_token(&tokens, new_token(res));
		else
			input++;
		while (*input == ' ')
			input++;
	}
	check_syntax(shell, tokens);
	return (tokens);
}
