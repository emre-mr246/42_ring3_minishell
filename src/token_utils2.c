/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:17:44 by mitasci           #+#    #+#             */
/*   Updated: 2024/09/25 12:46:22 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <limits.h>

int	check_syntax(t_shell *shell, t_tokens *token)
{
	t_tokens	*tmp;

	tmp = token;
	if (ft_strncmp(tmp->token, "|", 1) == 0)
		return (print_error(shell, NULL, ERR_SYNTAX, 0), 1);
	while (tmp && tmp->next)
	{
		if (ft_strncmp(tmp->token, "<", 1) == 0 && ft_strncmp(tmp->next->token,
				"|", 1) == 0)
			return (print_error(shell, NULL, ERR_SYNTAX, 0), 1);
		if (ft_strncmp(tmp->token, ">", 1) == 0 && ft_strncmp(tmp->next->token,
				"|", 1) == 0)
			return (print_error(shell, NULL, ERR_SYNTAX, 0), 1);
		tmp = tmp->next;
	}
	if (ft_strncmp(tmp->token, "|", 1) == 0)
		return (print_error(shell, NULL, ERR_SYNTAX, 0), 1);
	if (ft_strncmp(tmp->token, "<", 1) == 0)
		return (print_error(shell, NULL, ERR_SYNTAX, 0), 1);
	if (ft_strncmp(tmp->token, ">", 1) == 0)
		return (print_error(shell, NULL, ERR_SYNTAX, 0), 1);
	return (0);
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
