/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 06:14:29 by emgul            #+#    #+#             */
/*   Updated: 2024/07/06 18:46:14 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include <stdint.h>

/*
 * @brief Allocates memory for an array of count elements,
  each of size bytes, and initializes the allocated memory to zero.
 *
 * @param count Number of elements to allocate.
 * @param size  Size of each element in bytes.
 * @return      A pointer to the allocated memory block,
 *  or NULL if allocation fails.
 */
void	*ft_calloc(size_t count, size_t size)
{
	void	*result;
	size_t	res_size;

	if (count == 0 || size == 0)
		return (malloc(0));
	if (count > SIZE_MAX / size)
		return (NULL);
	res_size = count * size;
	result = malloc(res_size);
	if (!result)
		return (NULL);
	ft_bzero(result, res_size);
	return (result);
}
