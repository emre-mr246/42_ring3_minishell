/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:12:06 by emgul             #+#    #+#             */
/*   Updated: 2024/08/01 22:29:23 by emgul            ###   ########.fr       */
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
		if (ft_strncmp(tmp->key, key, ft_strlen(tmp->key)) == 0)
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
		if (ft_strncmp(tmp->key, key, ft_strlen(tmp->key)) == 0)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

static char *get_key(char **str)
{
	int i;
	char *res;

	i = 0;
	(*str)++;
	while ((*str)[i] && (*str)[i] != '$')
		i++;
	res = ft_substr(*str, 0, i);
	*str += i;
	return(res);
}

static char *get_value(char *key, t_env *env)
{
	t_env *tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(key, tmp->key, ft_strlen(key)) == 0)
			return(tmp->value);
		tmp = tmp->next;
	}
}

char *exchange_variable(char *str, t_env *env)
{
	int i;
	char *key;
	char *value;
	char *res;

	i = 0;
	res = (char *)malloc(sizeof(char) * 4096);
	if (!res)
		return (NULL);
	while (str && *str)
	{

		if (*str == '$')
		{
			key = get_key(&str);
			value = get_value(key, env);
			ft_strlcpy(res + i, value, ft_strlen(value) + 1);
			i += ft_strlen(value);
		}
		else
		{
			res[i] = *str;
			i++;
			str++;
		}
	}
	res[i] = '\0';
	return (res);
}
