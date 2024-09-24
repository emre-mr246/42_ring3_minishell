/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 13:32:17 by emgul             #+#    #+#             */
/*   Updated: 2024/09/19 18:38:35 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	check_odd_quotes(t_shell *shell, char *token)
{
	int		single_quote_num;
	int		double_quote_num;
	bool	single_quote;
	bool	double_quote;
	int		i;

	single_quote_num = 0;
	double_quote_num = 0;
	single_quote = false;
	double_quote = false;
	i = -1;
	while (token[++i])
	{
		if (token[i] == '\"' && !single_quote)
		{
			double_quote = !double_quote;
			double_quote_num++;
		}
		if (token[i] == '\'' && !double_quote)
		{
			single_quote = !single_quote;
			single_quote_num++;
		}
	}
	if (double_quote_num % 2 != 0 || single_quote_num % 2 != 0)
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
