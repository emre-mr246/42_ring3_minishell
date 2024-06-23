/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 05:01:25 by emgul             #+#    #+#             */
/*   Updated: 2023/12/02 05:01:25 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strnstr(char *haystack, char *needle, size_t n)
{
	size_t		i;
	size_t		j;

	if (*needle == '\0')
		return (haystack);
	i = 0;
	while (haystack[i] && i < n)
	{
		j = 0;
		while ((haystack[i + j] == needle[j]) && (i + j < n))
		{
			if (needle[j + 1] == '\0')
				return (haystack + i);
			j++;
		}
		i++;
	}
	return (NULL);
}
