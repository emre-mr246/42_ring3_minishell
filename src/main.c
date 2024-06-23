/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 00:48:40 by emgul             #+#    #+#             */
/*   Updated: 2024/06/23 22:28:01 by emgul            ###   ########.fr       */
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
		if (str[i] == '$')
			handle_dollar_sign();
		if (str[i] == '`')
			handle_backtick();
		if (str[i] == '\\')
			handle_backslash();	
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

int main(int ac, char **av, char **env)
{
	handle_single_quote("hello world' test");

	return (0);
}