/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 22:26:42 by emgul             #+#    #+#             */
/*   Updated: 2024/09/11 16:46:26 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

int	ft_find_index(char *haystack, char *needle)
{
	int	i;
	int	j;
	int	tmp;
	int	needle_len;

	needle_len = ft_strlen(needle);
	i = 0;
	while (haystack[i])
	{
		tmp = i;
		j = 0;
		while (haystack[tmp] == needle[j])
		{
			if (j + 1 == needle_len)
				return (i);
			tmp++;
			j++;
		}
		i++;
	}
	return (-1);
}

int	higher_len(char *str1, char *str2)
{
	int	len1;
	int	len2;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	if (len1 > len2)
		return (len1);
	else
		return (len2);
}

void	free_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_all(t_shell *shell)
{
	t_cmd		*tmp_cmd;
	t_tokens	*tmp_tokens;
	t_env		*tmp_env;

	while (shell->cmd)
	{
		tmp_cmd = shell->cmd;
		shell->cmd = shell->cmd->next;
		free_array(tmp_cmd->arr);
		free(tmp_cmd);
	}
	while (shell->tokens)
	{
		tmp_tokens = shell->tokens;
		shell->tokens = shell->tokens->next;
		free(tmp_tokens->token);
		free(tmp_tokens);
	}
	while (shell->env)
	{
		tmp_env = shell->env;
		shell->env = shell->env->next;
		free(tmp_env->key);
		free(tmp_env->value);
		free(tmp_env);
	}
	if (shell)
		free(shell);
}
