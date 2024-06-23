/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 20:35:50 by emgul             #+#    #+#             */
/*   Updated: 2024/06/22 20:36:58 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"
#include "../lib/libft/libft.h"

t_env *init_env(void)
{
	t_env *tmp;

	tmp = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!tmp)
		return (NULL);
	return (tmp);
}

void get_key(char *str, t_env *vars)
{
	int i;
	char *key;

	i = 0;
	while (ft_strchr(str, '=') && str[i] && str[i] != '=')
		i++;
	key = (char *)ft_calloc(i + 1, sizeof(char));
	if (!key)
		return ;
	ft_strlcpy(key, str, i + 1);
	vars->key = key;
}

void get_value(char *str, t_env *vars)
{
	char *value;

	str = ft_strchr(str, '=') + 1;
	if (!value)
		return ;
	value = ft_strdup(str);
}

void get_env(char **env)
{
	t_env *vars;

	vars = init_env();
	while (*env)
	{
		get_key(*env, vars);
		get_value(*env, vars);
		env++;
	}
}