/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 20:36:53 by emgul             #+#    #+#             */
/*   Updated: 2023/12/01 20:36:53 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t n)
{
	size_t	dst_counter;
	size_t	src_counter;

	dst_counter = 0;
	while (dst_counter < n && dst[dst_counter])
		dst_counter++;
	src_counter = 0;
	while ((dst_counter + src_counter + 1) < n && src[src_counter])
	{
		dst[dst_counter + src_counter] = src[src_counter];
		src_counter++;
	}
	if (dst_counter != n)
		dst[dst_counter + src_counter] = '\0';
	return (dst_counter + ft_strlen(src));
}
