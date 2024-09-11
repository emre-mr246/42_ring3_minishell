/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 06:14:28 by emgul             #+#    #+#             */
/*   Updated: 2023/12/01 06:14:28 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * @brief Checks whether the given character is a printable character.
 *
 * @param c The character to check.
 * @return 1 if the character is a printable 
 * character (between 32 and 126 inclusive), 0 otherwise.
 */
int	ft_isprint(int c)
{
	return (c >= 32 && c <= 126);
}
