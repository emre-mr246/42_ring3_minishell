/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 08:13:40 by emgul             #+#    #+#             */
/*   Updated: 2023/12/05 08:13:40 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	char	*result;
	size_t	src_len;

	if (!src)
		return (NULL);
	src_len = ft_strlen(src);
	result = (char *)malloc(sizeof(char) * (src_len + 1));
	if (!result)
		return (NULL);
	while (*src)
		*result++ = *src++;
	*result = '\0';
	result -= src_len;
	return (result);
}
