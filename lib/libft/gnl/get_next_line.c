/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 22:01:08 by emgul             #+#    #+#             */
/*   Updated: 2024/09/11 13:29:16 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static char	*malloc_null(void)
{
	char	*input_str;

	input_str = malloc(1);
	if (!input_str)
		return (NULL);
	input_str[0] = '\0';
	return (input_str);
}

char	*ft_append_to_left(int fd, char *input_str)
{
	char	buffer[BUFFER_SIZE + 1];
	int		bytes_read;
	char	*tmp;
	char	*new_str;

	if (!input_str)
		input_str = malloc_null();
	while (!ft_strchr(input_str, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(input_str), NULL);
		if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		tmp = input_str;
		new_str = ft_strjoin(tmp, buffer);
		if (!new_str)
			return (free(tmp), NULL);
		free(tmp);
		input_str = new_str;
	}
	return (input_str);
}

static char	*ft_get_line(char *input_str)
{
	char	*newline_ptr;
	char	*string;
	size_t	len;

	if (!input_str || !*input_str)
		return (NULL);
	newline_ptr = ft_strchr(input_str, '\n');
	if (!newline_ptr)
		len = ft_strlen(input_str) + 1;
	else
		len = (newline_ptr - input_str) + 1;
	string = (char *)malloc(sizeof(char) * len);
	if (!string)
		return (NULL);
	ft_strlcpy(string, input_str, len);
	return (string);
}

static char	*ft_extract_after_newline(char *input_str)
{
	char	*start;
	char	*result;
	size_t	result_size;

	start = input_str;
	while (*input_str && *input_str != '\n')
		input_str++;
	if (!*input_str)
	{
		free(start);
		return (NULL);
	}
	input_str++;
	result_size = ft_strlen(input_str);
	result = (char *)malloc(sizeof(char) * (result_size + 1));
	if (!result)
		return (NULL);
	while (*input_str)
		*result++ = *input_str++;
	*result = '\0';
	free(start);
	result -= result_size;
	return (result);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*input_str[4096];

	if (fd < 0 || fd > 4096 || BUFFER_SIZE <= 0)
		return (NULL);
	input_str[fd] = ft_append_to_left(fd, input_str[fd]);
	if (!input_str[fd])
		return (NULL);
	line = ft_get_line(input_str[fd]);
	input_str[fd] = ft_extract_after_newline(input_str[fd]);
	return (line);
}
