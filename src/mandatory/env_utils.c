/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:12:06 by emgul             #+#    #+#             */
/*   Updated: 2024/09/11 14:25:48 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	update_value(t_env *env, char *key, char *value)
{
	t_env	*tmp;

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

bool	key_exists(t_env *env, char *key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, higher_len(tmp->key, key)) == 0)
			return (true);
		tmp = tmp->next;
	}
	return (false);
}

char	*get_env_key(char *str)
{
	int		i;
	char	*res;

	i = 1;
	if (str[i] == '?')
		return (ft_strdup("?"));
	while (str[i] && str[i] != '$' && str[i] != '"' && str[i] != '\''
		&& str[i] != ' ')
		i++;
	if (i == 1)
		return (ft_strdup("$"));
	res = ft_substr(str, 1, i - 1);
	return (res);
}

char	*get_env_value(t_env *env, char *key)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, higher_len(tmp->key, key)) == 0)
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
