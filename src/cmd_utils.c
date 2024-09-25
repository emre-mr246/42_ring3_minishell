/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:32:17 by emgul             #+#    #+#             */
/*   Updated: 2024/09/25 12:39:48 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void	check_odd_quotes(t_shell *shell, char *token)
{
	int		quote_num[2];
	bool	single_quote;
	bool	double_quote;
	int		i;

	quote_num[0] = 0;
	quote_num[1] = 0;
	single_quote = false;
	double_quote = false;
	i = -1;
	while (token[++i])
	{
		if (token[i] == '\"' && !single_quote)
		{
			double_quote = !double_quote;
			quote_num[1]++;
		}
		if (token[i] == '\'' && !double_quote)
		{
			single_quote = !single_quote;
			quote_num[0]++;
		}
	}
	if (quote_num[1] % 2 != 0 || quote_num[0] % 2 != 0)
		print_error(shell, NULL, ERR_QUOTES, 1);
}

int	get_special_char_enum(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (*input == '|')
			return (PIPE);
		i++;
	}
	return (NONE);
}

int	cmd_len(t_cmd *cmd)
{
	t_cmd	*tmp;
	int		len;

	tmp = cmd;
	len = 0;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}
