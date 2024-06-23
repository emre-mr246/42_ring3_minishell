/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 14:41:02 by emgul             #+#    #+#             */
/*   Updated: 2023/12/10 18:37:24 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(char *str, int c)
{
	char	*last_char_pos;

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
