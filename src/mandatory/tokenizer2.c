/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 21:29:38 by emgul             #+#    #+#             */
/*   Updated: 2024/09/18 21:36:55 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

static int	is_sp(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

void	handle_space(char **res, char **str)
{
	int	i;

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
