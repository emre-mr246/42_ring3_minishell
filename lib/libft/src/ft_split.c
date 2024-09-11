/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:09:41 by emgul             #+#    #+#             */
/*   Updated: 2024/07/07 15:38:21 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static size_t	ft_countwords(char const *s, char c)
{
	size_t		word_count;

	word_count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			word_count++;
		while (*s && *s != c)
			s++;
	}
	return (word_count);
}

static char	**ft_split_main(char *s, char c, size_t word_count)
{
	char	**result;
	size_t	word_length;
	int		i;

	result = (char **)ft_calloc(sizeof(char *), (word_count + 1));
	if (!result)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s)
		{
			if (ft_strchr((char *)s, c))
				word_length = ft_strchr((char *)s, c) - s;
			else
				word_length = ft_strlen(s);
			result[i++] = ft_substr(s, 0, word_length);
			s += word_length;
		}
	}
	return (result);
}

char	**ft_split(char *s, char c)
{
	char	**result;
	size_t	word_count;

	if (!s)
		return (NULL);
	if (!*s)
		return ((char **)ft_calloc(sizeof(char *), 1));
	if (!c)
	{
		result = (char **)ft_calloc(sizeof(char *), 2);
		if (!result)
			return (NULL);
		result[0] = ft_strdup(s);
		return (result);
	}
	word_count = ft_countwords(s, c);
	if (word_count == 0)
		return ((char **)ft_calloc(sizeof(char *), 1));
	result = ft_split_main(s, c, word_count);
	return (result);
}

// int main()
// {
// 	char **test;

// 	test = ft_split("hello!", ' ');
// 	int a;
// }
