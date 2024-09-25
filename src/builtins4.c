/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 14:06:04 by mitasci           #+#    #+#             */
/*   Updated: 2024/09/25 10:31:02 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <unistd.h>
#include "readline/readline.h"
#include "readline/history.h"

static t_env	*get_prev_node(t_env *env, char *key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp->next)
	{
		if (ft_strncmp(tmp->next->key, key, higher_len(tmp->next->key,
					key)) == 0)
			break ;
		tmp = tmp->next;
	}
	return (tmp);
}

void	ft_unset_key(t_shell *shell, char *key)
{
	t_env	*node;
	t_env	*prev_node;
	t_env	*next_node;

	next_node = NULL;
	prev_node = NULL;
	node = NULL;
	if (ft_strncmp(shell->env->key, key, higher_len(shell->env->key, key) == 0))
	{
		next_node = shell->env->next;
		free_env(shell->env);
		shell->env = next_node;
		return ;
	}
	prev_node = get_prev_node(shell->env, key);
	node = prev_node->next;
	if (!node)
		return ;
	next_node = node->next;
	free_env(node);
	prev_node->next = next_node;
}
