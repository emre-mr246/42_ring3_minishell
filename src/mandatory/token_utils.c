/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:37:30 by mitasci           #+#    #+#             */
/*   Updated: 2024/09/16 15:39:00 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <limits.h>

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
		if ((*str)[i] == quote && ((*str)[i + 1] == ' ' || (*str)[i + 1] == '\0'
				|| (*str)[i + 1] >= 8 && (*str)[i + 1] <= 13))
		{
			res = ft_substr(*str, 0, i + 1);
			*str += i + 1;
			return (res);
		}
		i++;
	}
	return (NULL);
}

void	skip_whitespaces(char **str, int *i)
{
	while ((*str)[*i] == ' ' || ((*str)[*i] >= 8 && (*str)[*i] <= 13)
		|| ((*str)[*i] == '\\'))
		(*i)++;
}

void skip_quotes(char **str, int *i)
{
	char c;
	
	if ((*str)[*i] == '"' || (*str)[*i] == '\'')
	{
		c = (*str)[*i];
		(*i)++;
		while ((*str)[*i] != c)
			(*i)++;
	}
}

