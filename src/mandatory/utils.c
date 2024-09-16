/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 22:26:42 by emgul             #+#    #+#             */
/*   Updated: 2024/09/16 15:43:00 by mitasci          ###   ########.fr       */
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
		//free_array(tmp_cmd->arr);
		if (tmp_cmd->infile)
			free(tmp_cmd->infile);
		if (tmp_cmd->outfile)
			free(tmp_cmd->outfile);
		shell->cmd = shell->cmd->next;
		free(tmp_cmd);
	}
	while (shell->env)
	{
		tmp_env = shell->env;
		shell->env = shell->env->next;
		free(tmp_env->key);
		free(tmp_env->value);
		free(tmp_env);
	}
	if (shell->last_exit_status)
		free(shell->last_exit_status);
	if (shell)
		free(shell);
}

char	*allocate_str(t_shell *shell, int buff_size)
{
	char	*new;

	new = (char *)ft_calloc(sizeof(char), buff_size + 1);
	if (!new)
		print_error(shell, "HATA", NULL, ERR_MEMALLOC, 1);
	return (new);
}
