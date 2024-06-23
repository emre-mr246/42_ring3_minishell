/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 06:14:31 by emgul             #+#    #+#             */
/*   Updated: 2023/12/01 06:14:31 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	if ((dst == src) || (!src && !dst))
		return (dst);
	if (src < dst)
		while (n--)
			((char *)dst)[n] = ((char *)src)[n];
	else
		ft_memcpy(dst, (char *)src, n);
	return (dst);
}
