/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 04:46:57 by emgul             #+#    #+#             */
/*   Updated: 2023/12/02 04:46:57 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memchr(const void *ptr, int c, size_t n)
{
	unsigned char	*string;

	string = (unsigned char *)ptr;
	while (n--)
	{
		if (*string != (unsigned char)c)
			string++;
		else
			return (string);
	}
	return (0);
}
