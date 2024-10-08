/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mitasci <mitasci@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 22:26:42 by emgul             #+#    #+#             */
/*   Updated: 2024/09/23 18:04:59 by mitasci          ###   ########.fr       */
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

	if (!str1 || !str2)
		return (-1);
	len1 = ft_strlen(str1);
	len2 = ft_strlen(str2);
	if (len1 > len2)
		return (len1);
	else
		return (len2);
}

char	*allocate_str(t_shell *shell, int buff_size)
{
	char	*new;

	new = (char *)ft_calloc(sizeof(char), buff_size + 1);
	if (!new)
		print_error(shell, "HATA", ERR_MEMALLOC, 1);
	return (new);
}

int	str_in_array(char **arr, char *str)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		if (ft_strncmp(arr[i], str, higher_len(arr[i], str)) == 0)
			return (1);
		i++;
	}
	return (0);
}
