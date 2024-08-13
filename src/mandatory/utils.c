/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 22:26:42 by emgul             #+#    #+#             */
/*   Updated: 2024/08/14 00:50:13 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <unistd.h>
#include <stdlib.h>
#include "../../lib/libft/libft.h"





int	ft_find_index(char *haystack, char *needle)
{
	int	i;
	int	j;
	int	tmp;
	int needle_len;

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

int higher_len(char *str1, char *str2)
{
	int len1;
	int len2;

	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	if (len1 > len2)
		return (len1);
	else
		return (len2);
}

static void handle_dollar_sign(char **cmd, t_shell *shell)
{
	int i;
	char *res;

	i = 0;
	while(cmd[i])
	{
		res = exchange_variable(cmd[i], shell);
		if (!res)
			return ;
		cmd[i] = ft_strdup(res);
		if (!cmd[i])
			return ;
		i++;
	}
}

void dollar_sign(t_shell *shell)
{
	t_cmd *tmp;

	tmp = shell->cmd;
	while(tmp)
	{
		handle_dollar_sign(tmp->arr, shell);
		tmp = tmp->next;
	}
}
