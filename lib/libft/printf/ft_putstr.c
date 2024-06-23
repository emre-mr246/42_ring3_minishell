/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emgul <emgul@student.42istanbul.com.tr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 19:52:32 by emgul             #+#    #+#             */
/*   Updated: 2024/05/04 17:06:17 by emgul            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <unistd.h>
#include <stdarg.h>
#include <stdint.h>

int	ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

void	ft_putstr(char *str, t_format *f)
{
	if (!str)
	{
		f->printed_chars = write(1, "(null)", 6);
		return ;
	}
	while (*str)
		f->printed_chars += write(1, &*str++, 1);
}
