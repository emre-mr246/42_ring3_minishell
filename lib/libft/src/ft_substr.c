/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:02:21 by emgul             #+#    #+#             */
/*   Updated: 2023/12/05 11:02:21 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static size_t	str_len(char const *str)
{
	size_t	i;

	i = 0;
	while (*(str + i))
		i++;
	return (i);
}

static char	*str_new(size_t n)
{
	char	*str;

	str = (char *)ft_calloc(sizeof(char), (n + 1));
	if (!str)
		return (NULL);
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	char	*substr_ptr;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = str_len(s);
	if (start >= s_len)
		return (str_new(0));
	else if (len > (s_len - start))
		len = s_len - start;
	substr = str_new(len);
	if (!substr)
		return (NULL);
	s += start;
	substr_ptr = substr;
	while (len-- && *s)
		*substr++ = *s++;
	return (substr_ptr);
}
