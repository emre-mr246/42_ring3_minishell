/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 22:01:08 by emgul             #+#    #+#             */
/*   Updated: 2024/09/21 13:01:40 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/libft.h"
#include <unistd.h>

static char	*ft_append_to_left(int fd, char *input_str)
{
	char	*buffer;
	int		bytes_read;

	if (!input_str)
	{
		input_str = (char *)malloc(1 * sizeof(char));
		input_str[0] = '\0';
	}
	buffer = (char *)malloc(sizeof(char) * (BUFF_SIZE + 1));
	if (!buffer)
		return (NULL);
	bytes_read = 42;
	while (!ft_strchr(input_str, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFF_SIZE);
		if (bytes_read == -1)
			break ;
		buffer[bytes_read] = '\0';
		input_str = ft_strjoin(input_str, buffer);
	}
	free(buffer);
	return (input_str);
}

static char	*ft_get_line(char *input_str)
{
	char	*newline_ptr;
	char	*string;
	size_t	length;

	if (!input_str || !*input_str)
		return (NULL);
	newline_ptr = ft_strchr(input_str, '\n');
	if (!newline_ptr)
		length = ft_strlen(input_str);
	else
		length = newline_ptr - input_str + 1;
	string = (char *)malloc(sizeof(char) * (length + 1));
	if (!string)
		return (NULL);
	ft_strncpy_gnl(string, input_str, length);
	string[length] = '\0';
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

	if (fd < 0 || fd > 10240 || BUFF_SIZE <= 0)
		return (NULL);
	input_str[fd] = ft_append_to_left(fd, input_str[fd]);
	if (!input_str[fd])
		return (NULL);
	line = ft_get_line(input_str[fd]);
	input_str[fd] = ft_extract_after_newline(input_str[fd]);
	return (line);
}
