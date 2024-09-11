/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 06:14:26 by emgul             #+#    #+#             */
/*   Updated: 2023/12/01 06:14:26 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * @brief Checks whether the given character is a 7-bit ASCII character.
 *
 * @param c The character to check.
 * @return 1 if the character is a 7-bit ASCII character, 0 otherwise.
 */
int	ft_isascii(int c)
{
	return (c >= 0 && c <= 127);
}
