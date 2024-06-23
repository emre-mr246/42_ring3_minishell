/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 06:14:29 by emgul             #+#    #+#             */
/*   Updated: 2023/12/01 06:14:29 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t n)
{
	void	*result;

	if (!count || !n)
	{
		count = 1;
		n = 1;
	}
	result = malloc(count * n);
	if (!result)
		return (NULL);
	ft_bzero(result, count * n);
	return (result);
}
