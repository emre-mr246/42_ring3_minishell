/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:37:30 by mitasci           #+#    #+#             */
/*   Updated: 2024/09/25 12:46:06 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

char	*handle_comment(char *str)
{
	while (*str != '\n' || *str)
		str++;
	return (str);
}

int	handle_quote(char **res, char **str, char quote)
{
	int		i;

	i = 1;
	while ((*str)[i])
	{
		if ((*str)[i] == quote && ((*str)[i + 1] == ' ' || (*str)[i + 1] == '\0'
				|| ((*str)[i + 1] >= 8 && (*str)[i + 1] <= 13)))
		{
			ft_strlcpy(*res, *str, i + 2);
			*res += i + 1;
			*str += i + 1;
			return (0);
		}
		i++;
	}
	return (1);
}

void	skip_whitespaces(char **str, int *i)
{
	while ((*str)[*i] == ' ' || ((*str)[*i] >= 8 && (*str)[*i] <= 13)
		|| ((*str)[*i] == '\\'))
		(*i)++;
}

void	skip_quotes(char **str, int *i)
{
	char	c;

	if ((*str)[*i] == '"' || (*str)[*i] == '\'')
	{
		c = (*str)[*i];
		(*i)++;
		while ((*str)[*i] != c)
			(*i)++;
	}
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
