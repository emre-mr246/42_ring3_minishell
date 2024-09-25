/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 22:25:28 by emgul             #+#    #+#             */
/*   Updated: 2024/09/25 16:10:06 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <limits.h>

static int	is_sp(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

void	handle_space(char **res, char **str)
{
	int	i;

	i = 0;
	skip_whitespaces(str, &i);
	while ((*str) && (*str)[i])
	{
		skip_quotes(str, &i);
		if ((*str)[i] && ((*str)[i] == ' ' || ((*str)[i] >= 8
			&& (*str)[i] <= 13) || (*str)[i] == '\\' || is_sp((*str)[i])))
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

int	handle_special_char(char **res, char **input)
{
	int		i;
	char	*sp_char;

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

static void	write_to_res(char **res, char **input)
{
	int	res_i;

	res_i = 1;
	if ((**input == '\'' || **input == '\"') && *input)
		res_i = handle_quote(res, input, **input);
	if (*input && res_i)
		res_i = handle_special_char(res, input);
	if (*input && res_i)
		handle_space(res, input);
	**res = '\0';
}

t_tokens	*tokenizer(t_shell *shell, char *input, t_env *env)
{
	char		*res;
	char		*res_tmp;
	t_tokens	*tokens;

	tokens = NULL;
	while (input && *input && env)
	{
		while (*input == ' ' || (*input >= 8 && *input <= 13))
			input++;
		res = (char *)ft_calloc(sizeof(char), BUFFER_SIZE);
		if (!res)
			return (NULL);
		res_tmp = res;
		write_to_res(&res_tmp, &input);
		if (input && res)
			lstadd_back_token(&tokens, new_token(res));
		else
			input++;
		while (*input == ' ' || (*input >= 8 && *input <= 13))
			input++;
	}
	if (check_syntax(shell, tokens))
		return (free_token(tokens), NULL);
	return (tokens);
}
