/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 22:25:28 by emgul             #+#    #+#             */
/*   Updated: 2024/09/18 21:36:53 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <limits.h>

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

static int	get_indexes(char *input)
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

int	handle_special_char(char **res, char **input)
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
		free(sp_char);
		*res += ft_strlen(sp_char);
		*input += ft_strlen(sp_char);
	}
	return (i);
}

void	check_syntax(t_shell *shell, t_tokens *token)
{
	t_tokens	*tmp;

	tmp = token;
	if (ft_strncmp(tmp->token, "|", 1) == 0)
		print_error(shell, NULL, ERR_SYNTAX, 1);
	while (tmp && tmp->next)
	{
		if (ft_strncmp(tmp->token, "<", 1) == 0 && ft_strncmp(tmp->next->token,
				"|", 1) == 0)
			print_error(shell, NULL, ERR_SYNTAX, 1);
		if (ft_strncmp(tmp->token, ">", 1) == 0 && ft_strncmp(tmp->next->token,
				"|", 1) == 0)
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
