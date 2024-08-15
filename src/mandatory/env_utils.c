/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:12:06 by emgul             #+#    #+#             */
/*   Updated: 2024/08/15 21:47:10 by mitasci          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../lib/libft/libft.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

void update_value(t_env *env, char *key, char *value)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, higher_len(tmp->key, key)) == 0)
			break ;
		tmp = tmp->next;
	}
	if (!tmp)
		return ;
	free(tmp->value);
	tmp->value = ft_strdup(value);
}

bool key_exists(t_env *env, char *key)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, higher_len(tmp->key, key)) == 0)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

char *get_env_key(char *str)
{
	int i;
	char *res;

	i = 1;
	if (str[i] == '?')
		return ft_strdup("?");
	while (str[i] && str[i] != '$' && str[i] != '"' && str[i] != '\'' && str[i] != ' ')
		i++;
	if (i == 1)
		return ft_strdup("$");
	res = ft_substr(str, 1, i - 1);
	return (res);
}

char *get_env_value(t_env *env, char *key)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, higher_len(tmp->key, key)) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

// char *exchange_variable(char *str, t_shell *shell)
// {
// 	int i;
// 	char *key;
// 	char *value;
// 	char *res;

// 	res = (char *)malloc(sizeof(char) * 4096);
// 	if (!res)
// 		return (NULL);
// 	i = 0;
// 	while (str && *str)
// 	{
// 		if (*str == '$')
// 		{
// 			key = get_env_key(&str);
// 			if (!key)
// 				return (NULL);
// 			if (ft_strncmp(key, "?", higher_len(key, "?")) == 0)
// 				value = ft_itoa(*shell->last_exit_status);
// 			else
// 				value = get_env_value(shell->env, key);
// 			ft_strlcpy(res + i, value, ft_strlen(value) + 1);
// 			i += ft_strlen(value);
// 		}
// 		else
// 			res[i++] = *str++;
// 	}
// 	res[i] = '\0';
// 	return (res);
// }


