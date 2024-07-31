/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 20:35:50 by emgul             #+#    #+#             */
/*   Updated: 2024/07/31 08:28:20 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include "../../lib/libft/libft.h"

t_env	*env_lstlast(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	env_lstadd_back(t_env **lst, t_env *new)
{
	t_env	*tmp;

	if (!new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return ;
}

t_env *init_env(void)
{
	t_env *tmp;

	tmp = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!tmp)
		return (NULL);
	return (tmp);
}

static void get_key(char *str, t_env *vars)
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
	str = ft_strchr(str, '=') + 1;
	if (!str)
		return ;
	vars->value = ft_strdup(str);
}


t_env *get_env(char **env)
{
	t_env *vars;
	t_env *tmp;

	if (!env || !*env)
		return (NULL);
	vars = init_env();
	get_key(*env, vars);
	get_value(*env, vars);
	env++;
	tmp = vars;
	while (*env)
	{
		tmp = init_env();
		get_key(*env, tmp);
		get_value(*env, tmp);
		env_lstadd_back(&vars, tmp);
		env++;
	}
	return (vars);
}
