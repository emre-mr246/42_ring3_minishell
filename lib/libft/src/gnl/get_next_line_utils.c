/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 22:01:00 by emgul             #+#    #+#             */
/*   Updated: 2024/07/07 15:06:05 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"

char	*ft_strjoin_gnl(char *input_str, char *buffer)
{
	size_t	i;
	size_t	j;
	size_t	result_len;
	char	*result;

	result_len = ft_strlen(input_str) + ft_strlen(buffer);
	result = (char *)malloc(sizeof(char) * (result_len + 1));
	if (!result)
		return (NULL);
	i = -1;
	j = 0;
	while (input_str[++i])
		result[i] = input_str[i];
	while (buffer[j])
		result[i++] = buffer[j++];
	result[result_len] = '\0';
	free(input_str);
	return (result);
}

char	*ft_strncpy_gnl(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (src[i] && i < n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}
