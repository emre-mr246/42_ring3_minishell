/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 14:41:02 by emgul             #+#    #+#             */
/*   Updated: 2024/07/07 15:19:08 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strrchr(char *str, int c)
{
	char	*last_char_pos;

	if (!str)
		return (NULL);
	last_char_pos = NULL;
	while (*str)
	{
		if (*str == (char)c)
			last_char_pos = str;
		str++;
	}
	if (*str == (char)c)
		return (str);
	else
		return (last_char_pos);
}
