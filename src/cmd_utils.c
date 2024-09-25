/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:32:17 by emgul             #+#    #+#             */
/*   Updated: 2024/09/25 16:09:47 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

static int	count_quotes(char c, char quote, bool *single_quote,
		bool *double_quote)
{
	int	quote_num;

	quote_num = 0;
	if (c == quote && !(*double_quote))
	{
		*single_quote = !*single_quote;
		quote_num++;
	}
	return (quote_num);
}

int	check_odd_quotes(t_shell *shell, char *str)
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
	while (str[++i])
	{
		quote_num[0] += count_quotes(str[i], '\'', &single_quote,
				&double_quote);
		quote_num[1] += count_quotes(str[i], '\"', &double_quote,
				&single_quote);
	}
	if (quote_num[1] % 2 != 0 || quote_num[0] % 2 != 0)
		return (print_error(shell, NULL, ERR_QUOTES, 0), 1);
	return (0);
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
