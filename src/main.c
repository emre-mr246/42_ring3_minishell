/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:48:40 by emgul             #+#    #+#             */
/*   Updated: 2024/06/23 23:26:36 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "readline/readline.h"
#include "readline/history.h"
#include "../lib/libft/libft.h"
#include "../inc/minishell.h"

char *handle_comment(char *str)
{
	while(*str != '\n' || *str)
		str++;
	return (str);
}

char *handle_single_quote(char *str)
{
	int i;
	char	*res;

	i = 0;
	while(str[i])
	{
		if (str[i] == '\'')
		{
			res = ft_substr(str, 0, i);
			printf("res: %s\n", res);
			return (res);
		}
		i++;
	}
	return (NULL);
}



char *handle_double_quote(char *str)
{
	int i;
	char	*res;

	i = 0;
	while(str[i])
	{
		// if (str[i] == '$')
		// 	handle_dollar_sign();
		// if (str[i] == '`')
		// 	handle_backtick();
		// if (str[i] == '\\')
		// 	handle_backslash();	
		if (str[i] == '\"')
		{
			res = ft_substr(str, 0, i);
			printf("res: %s\n", res);
			return (res);
		}
		i++;
	}
	return (NULL);
}


// char **parse_input(char *input)
// {
// 	char **input_array;

	
	
// }
t_env	*env_lstlast_kek(t_env *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
int main(int ac, char **av, char **env)
{
	t_env *environment;
	environment = get_env(env);
	// printf("Bkey: %s\n", environment->key);
	// printf("Bvalue: %s\n", environment->value);
	// printf("key: %s\n", env_lstlast_kek(environment)->key);
	// printf("value: %s\n", env_lstlast_kek(environment)->value);
	// handle_single_quote("hello world' test");

	return (0);
}